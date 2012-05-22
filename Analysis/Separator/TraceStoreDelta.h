/* Copyright (C) 2010 Ion Torrent Systems, Inc. All Rights Reserved */
#ifndef TRACESTOREDELTA_H
#define TRACESTOREDELTA_H

#include <algorithm>
#include "Mask.h"
#include "TraceStore.h"
#include "MathOptim.h"
#include "GridMesh.h"

/**
 * Abstract interface to a repository for getting traces.
 */
template <typename T, typename IT=char>
class TraceStoreDelta : public TraceStore<T>
{

  public:

    void SetMinRefProbes (int n)
    {
      mMinRefProbes = n;
    }

    TraceStoreDelta (Mask &mask, size_t frames, const char *flowOrder,
                     int numFlowsBuff, int maxFlow, int rowStep, int colStep)
    {
      pthread_mutex_init (&mLock, NULL);
      mUseMeshNeighbors = 1;
      mRowRefStep = rowStep;
      mColRefStep = colStep;
      mMinRefProbes = floor (mRowRefStep * mColRefStep * .1);
      mRows = mask.H();
      mCols = mask.W();
      mFrames = frames;

      mFlowOrder = flowOrder;
      mFlowToBufferIndex.resize (maxFlow);
      std::fill (mFlowToBufferIndex.begin(), mFlowToBufferIndex.end(), -1);

      mWells = mRows * mCols;
      mUseAsReference.resize (mWells, false);
      mWellIndex.resize (mWells);
      std::fill (mWellIndex.begin(), mWellIndex.end(), -1);
      int keep = 0;
      int empties = 0;
      for (size_t i = 0; i < mWells; i++)
      {
        if (! (mask[i] & MaskExclude))
        {
          mWellIndex[i] = keep++;
        }
        if (mask[i] & MaskEmpty)
        {
          mUseAsReference[i]  = true;
          empties++;
        }
      }
      cout << "Got : " << empties << " empties." << endl;
      mFlowsBuf = numFlowsBuff;
      mRefGridsValid.resize (mFlowsBuf, 0);
      mRefGrids.resize (mFlowsBuf);
      mBufferIndexToFlow.resize (mFlowsBuf);
      std::fill (mBufferIndexToFlow.begin(), mBufferIndexToFlow.end(), -1);

      mData.resize (keep * mFrames * mFlowsBuf);
      std::fill (mData.begin(), mData.end(), 0);
    }

    ~TraceStoreDelta()
    {
      pthread_mutex_destroy (&mLock);
    }


    void SetFlowIndex (size_t flowIx, size_t index)
    {
      ION_ASSERT (flowIx < mFlowToBufferIndex.size(), "Flow index requested is larger than max flow.");
      ION_ASSERT (index < mFlowsBuf, "Index requested is larger than buffer size.");
      //ION_ASSERT(flowIx >= 0, "Flow must be positive.");
      if (mBufferIndexToFlow[index] >= 0)
      {
        mFlowToBufferIndex[mBufferIndexToFlow[index]] = -1;
      }
      mRefGridsValid[index] = 0;
      mFlowToBufferIndex[flowIx] = index;
    }

    size_t GetNumFrames() { return mFrames; }
    size_t GetNumWells() { return mRows * mCols; }
    size_t GetNumRows() { return mRows; }
    size_t GetNumCols() { return mCols; }
    const std::string &GetFlowOrder() { return mFlowOrder; }
    double GetTime (size_t frame) { return mTime.at (frame); }
    void SetTime (Col<double> &time) { mTime = time; }
    size_t GetFlowBuff() { return mFlowsBuf; }

    bool HaveWell (size_t wellIx)
    {
      return mWellIndex[wellIx] >= 0;
    }

    void SetHaveWellFalse (size_t wellIx)
    {
      mWellIndex[wellIx] = -1;
    }

    bool HaveFlow (size_t flowIx)
    {
      return mFlowToBufferIndex[flowIx] >= 0;
    }

    void SetReference(size_t wellIx, bool isReference) { mUseAsReference[wellIx] = isReference; }

    bool IsReference (size_t wellIx)
    {
      return mUseAsReference[wellIx];
    }

    int GetTrace (size_t wellIx, size_t flowIx, typename std::vector<T>::iterator traceBegin)
    {
      int wIdx = mWellIndex[wellIx];
      int fIdx = mFlowToBufferIndex[flowIx];
      ION_ASSERT (wIdx >= 0, "Not valid: " + ToStr(wellIx));
      assert (fIdx >= 0);
      if (wIdx >= 0 && fIdx >= 0)
      {
        (*traceBegin) = mData[ToIdx (wIdx, 0, fIdx) ];
        for (size_t i = 1; i < mFrames; i++)
        {
          float next = (*traceBegin) + (mData[ToIdx (wIdx, i, fIdx) ]);
          * (++traceBegin) = next;
        }
      }
      return OK;
    }

    int GetTrace (size_t wellIx, size_t flowIx, typename arma::Col<double>::col_iterator traceBegin)
    {
      int wIdx = mWellIndex[wellIx];
      int fIdx = mFlowToBufferIndex[flowIx];
      assert (wIdx >= 0);
      assert (fIdx >= 0);
      if (wIdx >= 0 && fIdx >= 0)
      {
        *traceBegin = mData[ToIdx (wIdx,0, fIdx) ];
        for (size_t i = 1; i < mFrames; i++)
        {
          float next = (*traceBegin) + (mData[ToIdx (wIdx, i, fIdx) ]);
          * (++traceBegin) = next;
        }
      }
      return OK;
    }

    int SetTrace (size_t wellIx, size_t flowIx,
                  typename std::vector<double>::iterator traceBegin, typename std::vector<double>::iterator traceEnd)
    {
      int wIdx = mWellIndex[wellIx];
      int fIdx = mFlowToBufferIndex[flowIx];
      assert (wIdx >= 0);
      assert (fIdx >= 0);
      double sum = 0;
      size_t frameIx = 0;
      while (traceBegin != traceEnd)
      {
        float tmp = (*traceBegin) - sum;
        assert (frameIx < mFrames);
        if (tmp >= std::numeric_limits<int8_t>::max())
        {
          mData[ToIdx (wIdx, frameIx, flowIx) ] = std::numeric_limits<int8_t>::max();
        }
        if (tmp <= (-1 * std::numeric_limits<int8_t>::max()))
        {
          mData[ToIdx (wIdx, frameIx, flowIx) ] = -1 * std::numeric_limits<int8_t>::max();
        }
        else
        {
          mData[ToIdx (wIdx, frameIx, flowIx) ] = (int8_t) (tmp + .5);
        }
        sum += mData[ToIdx (wIdx, frameIx, flowIx) ];
        ++frameIx;
        ++traceBegin;
      }
      return OK;
    }

    int SetTrace (size_t wellIx, size_t flowIx,
                  typename arma::Col<double>::col_iterator traceBegin, typename arma::Col<double>::col_iterator traceEnd)
    {
      int wIdx = mWellIndex[wellIx];
      int fIdx = mFlowToBufferIndex[flowIx];
      assert (wIdx >= 0);
      assert (fIdx >= 0);
      double sum = 0;
      size_t frameIx = 0;
      while (traceBegin != traceEnd)
      {
        float tmp = (*traceBegin) - sum;
        assert (frameIx < mFrames);
        if (tmp >= std::numeric_limits<int8_t>::max())
        {
          mData[ToIdx (wIdx, frameIx, flowIx) ] = std::numeric_limits<int8_t>::max();
        }
        if (tmp <= (-1 * std::numeric_limits<int8_t>::max()))
        {
          mData[ToIdx (wIdx, frameIx, flowIx) ] = -1 * std::numeric_limits<int8_t>::max();
        }
        else
        {
          mData[ToIdx (wIdx, frameIx, flowIx) ] = (int8_t) (tmp + .5);
        }
        sum += mData[ToIdx (wIdx, frameIx, flowIx) ];
        ++frameIx;
        ++traceBegin;
      }
      return OK;
    }

    size_t RowColToIndex (size_t rowIx, size_t colIx) { return rowIx * mCols + colIx; }

    void IndexToRowCol (size_t index, size_t &rowIx, size_t &colIx)
    {
      rowIx = index / mCols;
      colIx = index % mCols;
    }

    virtual int PrepareReference (size_t flowIx)
    {
      int fIdx = mFlowToBufferIndex[flowIx];
      CalcReference (mRowRefStep, mColRefStep, flowIx, mRefGrids[fIdx]);
      mRefGridsValid[fIdx] = 1;
      mFineRefGrids.resize (mRefGrids.size());
      mFineRefGrids[fIdx].Init (mRows, mCols, 50, 50);
      int numBin = mFineRefGrids[fIdx].GetNumBin();
      int rowStart = -1, rowEnd = -1, colStart = -1, colEnd = -1;
      for (int binIx = 0; binIx < numBin; binIx++)
      {
        mFineRefGrids[fIdx].GetBinCoords (binIx, rowStart, rowEnd, colStart, colEnd);
        vector<float> &trace = mFineRefGrids[fIdx].GetItem (binIx);
        CalcMedianReference ( (rowEnd + rowStart) /2, (colEnd + colStart) /2, mRefGrids[fIdx],
                              mDist, mValues, trace);
      }
      return OK;
    }

    virtual int GetReferenceTrace (size_t wellIx, size_t flowIx,
                                   typename arma::Col<T>::col_iterator traceBegin)
    {
      int wIdx = mWellIndex[wellIx];
      int fIdx = mFlowToBufferIndex[flowIx];
      assert (wIdx >= 0);
      assert (fIdx >= 0);
      size_t row, col;
      IndexToRowCol (wellIx, row, col);
      vector<float> &ref = mFineRefGrids[fIdx].GetItemByRowCol (row, col);
      copy (ref.begin(), ref.end(), traceBegin);
      return OK;
    }

    virtual void SetT0 (std::vector<float> &t0)
    {
      mT0 = t0;
    }

    virtual float GetT0 (int idx)
    {
      return mT0[idx];
    }

  private:
    /** wIx is the well index from mWellIndex, not the usual global one. */
    size_t ToIdx (size_t wIx, size_t frameIx, size_t flowIx)
    {
      // Organize so flows for same well are near each other.
      return (wIx * mFlowsBuf * mFrames + mFlowToBufferIndex[flowIx] * mFrames + frameIx);
    }

  void SmoothTrace(std::vector<float> &reference);

    int CalcMedianReference (size_t row, size_t col,
                             GridMesh<std::vector<float> > &regionMed,
                             std::vector<double> &dist,
                             std::vector<std::vector<float> *> &values,
                             std::vector<float> &reference)
    {
      int retVal = TraceStore<T>::TS_OK;
      bool ok = false;
      int maxDist = 4;
      int binDist = mUseMeshNeighbors;
      // Look farther and farther out for some good references as necessary
      while (!ok && binDist < maxDist) {
        regionMed.GetClosestNeighbors (row, col, binDist, dist, values);
        size_t size = 0;
        for (size_t i = 0; i < values.size(); i++) { size = max (values[i]->size(), size); }
        reference.resize (size);
        if (size == 0) {
          binDist++;
        }
        else {
          ok = true;
        }
      }
      std::fill (reference.begin(), reference.end(), 0.0);
      double distWeight = 0;
      size_t valSize = values.size();
      for (size_t i = 0; i < valSize; i++)
      {
        if (values[i]->size()  == 0)
        {
          continue;
        }
        double w = TraceStore<T>::WeightDist (dist[i]); //1/sqrt(dist[i]+1);
        distWeight += w;
        size_t vSize = values[i]->size();
        for (size_t j = 0; j < vSize; j++)
        {
          reference[j] += w * values[i]->at (j);
        }
      }
      // Divide by our total weight to get weighted mean
      if (distWeight > 0)
      {
        for (size_t i = 0; i < reference.size(); i++)
        {
          reference[i] /= distWeight;
        }
        retVal = TraceStore<T>::TS_OK;
      }
      else
      {
        retVal = TraceStore<T>::TS_BAD_DATA;
      }
      return retVal;
    }

    int CalcRegionReference (int rowStart, int rowEnd,
                             int colStart, int colEnd, size_t flowIx,
                             std::vector<float> &trace)
    {
      trace.resize (mFrames);
      std::fill (trace.begin(), trace.end(), 0.0f);
      vector<vector<float> > matrix;
      vector<double> traceBuffer (mFrames,0);
      matrix.resize (trace.size());
      for (int rowIx = rowStart; rowIx < rowEnd; rowIx++)
      {
        for (int colIx = colStart; colIx < colEnd; colIx++)
        {
          size_t wellIdx = RowColToIndex (rowIx,colIx);
          if (mUseAsReference[wellIdx])
          {
            GetTrace (wellIdx, flowIx, traceBuffer.begin());
            for (size_t frameIx = 0; frameIx < traceBuffer.size(); frameIx++)
            {
              if (isfinite (traceBuffer[frameIx]))
              {
                matrix[frameIx].push_back (traceBuffer[frameIx]);
              }
            }
          }
        }
      }
      size_t length = matrix[0].size();
      size_t size = matrix.size();
      if (length >= mMinRefProbes)
      {
        for (size_t i = 0; i < size; i++)
        {
          std::sort (matrix[i].begin(), matrix[i].end());
          float med = 0;
          if (matrix[i].size() % 2 == 0)
          {
            med = (matrix[i][length / 2] + matrix[i][ (length / 2)-1]) /2.0;
          }
          else
          {
            med = matrix[i][length/2];
          }
          trace[i] = med;
        }
        return TraceStore<T>::TS_OK;
      }
      else
      {
        trace.resize (0);
      }
      return TraceStore<T>::TS_BAD_REGION;
    }


    void SetMeshDist (int size) { mUseMeshNeighbors = size; }
    int GetMeshDist() { return mUseMeshNeighbors; }

    void CalcReference (size_t rowStep, size_t colStep, size_t flowIx,
                        GridMesh<std::vector<float> > &gridReference)
    {
      gridReference.Init (mRows, mCols, rowStep, colStep);
      int numBin = gridReference.GetNumBin();
      int rowStart = -1, rowEnd = -1, colStart = -1, colEnd = -1;
      for (int binIx = 0; binIx < numBin; binIx++)
      {
        gridReference.GetBinCoords (binIx, rowStart, rowEnd, colStart, colEnd);
        vector<float> &trace = gridReference.GetItem (binIx);
        CalcRegionReference (rowStart, rowEnd, colStart, colEnd, flowIx, trace);
      }
    }

  private:
    size_t mFrames;
    size_t mRows;
    size_t mCols;
    size_t mWells;
    size_t mFlowsBuf;
    size_t mRowRefStep;
    size_t mColRefStep;
    size_t mMinRefProbes;

    std::string mFlowOrder;
    std::vector<bool> mUseAsReference;
    std::vector<int> mFlowToBufferIndex;
    std::vector<int> mBufferIndexToFlow;
    std::vector<int> mWellIndex;
    std::vector<int8_t> mData;
    std::vector<int> mRefGridsValid;
    std::vector<GridMesh<std::vector<float> > > mRefGrids;
    std::vector<GridMesh<std::vector<float> > > mFineRefGrids;
    std::vector<double> mDist;
    std::vector<std::vector<float> *> mValues;
    std::vector<float> mReference;
    std::vector<float> mT0;
    arma::Col<double> mTime;
    // Cube<int8_t> mData;  // rows = frames, cols = wells,
    pthread_mutex_t mLock;
    int mUseMeshNeighbors;
};

#endif // TRACESTOREDELTA_H
