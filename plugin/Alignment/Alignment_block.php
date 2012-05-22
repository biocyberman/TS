<html>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">

<head>
<?php
include("library/Alignment_Library.php");
?>

        <link rel="stylesheet" type="text/css" href="/site_media/stylesheet.css"/>
        <script type="text/javascript" src="/site_media/jquery/js/jquery-1.7.1.min.js"></script>
        <!--script type="text/javascript" src="https://ajax.googleapis.com/ajax/libs/jquery/1.7.1/jquery.min.js"></script-->
        <link type="text/css" href="/site_media/jquery/css/aristo/jquery-ui-1.8.7.custom.css" rel="Stylesheet" />
        <script type="text/javascript" src="/site_media/jquery/js/tipTipX/jquery.tipTipX.js"></script>
        <link href="/site_media/jquery/js/tipTipX/jquery.tipTipX.css" rel="stylesheet" type="text/css"/>
        <link rel="stylesheet" type="text/css" href="/site_media/jquery/colorbox/colorbox.css" media="screen" />
        <link href='/site_media/jquery/js/tipTipX/jquery.tipTipX.css' rel='stylesheet' type='text/css' />
        <script type="text/javascript" src="/site_media/jquery/colorbox/jquery.colorbox-min.js"></script>
        <script type="text/javascript" src="/site_media/jquery/js/jquery.tools.min.js"></script>
        <script type="text/javascript" src="/site_media/jquery/js/jquery.activity-indicator-1.0.0.min.js"></script>

        <!-- style for the reports -->
        <link rel="stylesheet" type="text/css" href="/site_media/report.css" media="screen" />



 <script type="text/javascript">

 $(document).ready(function(){

         $(".noheading tr:odd").addClass("zebra");
          $(".heading tr:odd").addClass("zebra");
          $(".heading tbody tr").live("mouseover", function(){
                $(this).addClass("table_hover");
           });
          $(".heading tbody tr").live("mouseout", function(){
                $(this).removeClass("table_hover");
           });
          $(".noheading tbody tr").live("mouseover", function(){
                $(this).addClass("table_hover");
           });
          $(".noheading tbody tr").live("mouseout", function(){
                $(this).removeClass("table_hover");
            });
});

</script>
</head>
<body>
<?php

                        $startplugin = "startplugin.json";
                        if(!file_exists($startplugin))
                        {
                          die("File - ". $startplugin ." not found");
                        }
                        else
                        {
                            $analysis_json = file_get_contents($startplugin, FILE_IGNORE_NEW_LINES and FILE_SKIP_EMPTY_LINES);
                        }

                        $analysis_json = json_decode($analysis_json, true);
                        
                        $reportlayout = "../../report_layout.json";
                        if(!file_exists($reportlayout))
                        {
                            die("File - ". $reportlayout. " not found");
                        }
                        else
                        {
                            $json = file_get_contents($reportlayout, FILE_IGNORE_NEW_LINES and FILE_SKIP_EMPTY_LINES);
                        }

                        $layout = json_decode($json,true);
                        $as = parse_to_keys($layout["Alignment Summary"]["file_path"]);
                        print "<h3 style='margin-left:-14px;'> Re-Alignment to Genome: " . $as['Genome'] . "</h3>";
                        $filename = glob("*.zip");
			if (file_exists($filename[0])) {
				$link_name = $analysis_json['runinfo']['url_root'] . "/plugin_out/Alignment_out/" . $filename[0];
				print "<a href='$link_name'>Download Output Files</a>";
			}
                        print "<h3 style='margin-left:-14px;'> Based on Re-Alignment to Provided Reference</h3>";
           		$json = file_get_contents('../../report_layout.json', FILE_IGNORE_NEW_LINES and FILE_SKIP_EMPTY_LINES);
                        //once we have as we can check to see if it contains the full data, or the sampled data
                        if (isset($as['Total number of Sampled Reads'])) {
                                $align_full = false;
                        }else{
                                $align_full = true;
                        }



				 if($align_full == true && $as){

        			print "<script>$('.tip').tipTip({ position : 'bottom' });</script>";
                                print '<table id="alignment" class="heading" style="width: 100%; margin-left:0px;" >';
                                print "<col width='300px' />";
                                print "<col width='173px' />";
                                print "<col width='173px' />";
                                print "<col width='173px' />";

                                print "<thead><tr><th> </th>";

                                //header info here
                                print "<th>AQ17</th>";
                                print "<th>AQ20</th>";
                                print "<th>Perfect</th>";

                                print "</tr></thead><tbody>";

                                print "<tr>";
                                        print "<th>Total Number of Bases [Mbp]</th>";
                                        //Convert bases to megabases
                                        print "<td>" . local_try_number_format( $as['Filtered Mapped Bases in Q17 Alignments']/1000000 , 2 ) ."</td>";
                                        print "<td>" . local_try_number_format( $as['Filtered Mapped Bases in Q20 Alignments']/1000000 , 2 ) ."</td>";
                                        print "<td>" . local_try_number_format( $as['Filtered Mapped Bases in Q47 Alignments']/1000000 , 2 ) ."</td>";
                                print "</tr>";

                                print "<tr>";
                                        print "<th>Mean Length [bp]</th>";
                                        print "<td>" . local_try_number_format( $as['Filtered Q17 Mean Alignment Length']) ."</td>";
                                        print "<td>" . local_try_number_format( $as['Filtered Q20 Mean Alignment Length']) ."</td>";
                                        print "<td>" . local_try_number_format( $as['Filtered Q47 Mean Alignment Length']) ."</td>";
                                print "</tr>";

                                print "<tr>";
                                        print "<th>Longest Alignment [bp]</th>";
                                        print "<td>" . local_try_number_format( $as['Filtered Q17 Longest Alignment']) ."</td>";
                                        print "<td>" . local_try_number_format( $as['Filtered Q20 Longest Alignment']) ."</td>";
                                        print "<td>" . local_try_number_format( $as['Filtered Q47 Longest Alignment']) ."</td>";
                                print "</tr>";

                                print "<tr>";
                                        print "<th>Mean Coverage Depth</th>";
                                        print "<td>" . local_try_number_format( $as['Filtered Q17 Mean Coverage Depth'], 2) ."&times;</td>";
                                        print "<td>" . local_try_number_format( $as['Filtered Q20 Mean Coverage Depth'], 2) ."&times;</td>";
                                        print "<td>" . local_try_number_format( $as['Filtered Q47 Mean Coverage Depth'], 2) ."&times;</td>";
                                print "</tr>";

                                print "<tr>";
                                        print "<th>Percentage of Library Covered</th>";
                                        print "<td>" . local_try_number_format( $as['Filtered Q17 Coverage Percentage']) ."%</td>";
                                        print "<td>" . local_try_number_format( $as['Filtered Q20 Coverage Percentage']) ."%</td>";
                                        print "<td>" . local_try_number_format( $as['Filtered Q47 Coverage Percentage']) ."%</td>";
                                print "</tr>";

                                print "</tbody>";
                                print "</table>";

                        }elseif ($align_full == false && $as){
                                print '<h3>Based on Sampled Library Alignment to Provided Reference</h3>';

				print "<script>$('.tip').tipTip({ position : 'bottom' });</script>";
                                print '<table id="alignment" class="heading" style="width: 100%; margin-left:0px;" >';
                                print "<col width='300px' />";

                                print "<col width='86px' />";
                                print "<col width='86px' />";
                                print "<col width='86px' />";
                                print "<col width='86px' />";
                                print "<col width='86px' />";
                                print "<col width='86px' />";


                                print "<thead><tr> <th class='empty'> </th>";
                                print "<th colspan=3 class='tiptop'>Random sample of " . local_try_number_format($as['Total number of Sampled Reads']) . " reads</th>";
                                print "<th colspan=3 class='tiptop'>Extrapolation to all " . local_try_number_format($as['Total number of Reads']) . " reads</th></tr>";

                                //header info here
                                print "<th> </th>";
                                print "<th>AQ17</th>";
                                print "<th>AQ20</th>";
                                print "<th>Perfect</th>";
                                print "<th>AQ17</th>";
                                print "<th>AQ20</th>";
                                print "<th>Perfect</th>";

                                print "</tr></thead><tbody>";

                                print "<tr>";
                                        print "<th>Total Number of Bases [Mbp]</th>";
                                        //Convert bases to megabases
                                        print "<td>" . local_try_number_format( $as['Sampled Filtered Mapped Bases in Q17 Alignments']/1000000 , 2 ) ."</td>";
                                        print "<td>" . local_try_number_format( $as['Sampled Filtered Mapped Bases in Q20 Alignments']/1000000 , 2 ) ."</td>";
                                        print "<td>" . local_try_number_format( $as['Sampled Filtered Mapped Bases in Q47 Alignments']/1000000 , 2 ) ."</td>";
                                        print "<td>" . local_try_number_format( $as['Extrapolated Filtered Mapped Bases in Q17 Alignments']/1000000 , 2 ) ."</td>";
                                        print "<td>" . local_try_number_format( $as['Extrapolated Filtered Mapped Bases in Q20 Alignments']/1000000 , 2 ) ."</td>";
                                        print "<td>" . local_try_number_format( $as['Extrapolated Filtered Mapped Bases in Q47 Alignments']/1000000 , 2 ) ."</td>";
                                print "</tr>";

                                print "<tr>";
                                        print "<th>Mean Length [bp]</th>";
                                        print "<td>" . local_try_number_format( $as['Sampled Filtered Q17 Mean Alignment Length']) ."</td>";
                                        print "<td>" . local_try_number_format( $as['Sampled Filtered Q20 Mean Alignment Length']) ."</td>";
                                        print "<td>" . local_try_number_format( $as['Sampled Filtered Q47 Mean Alignment Length']) ."</td>";
                                        print "<td>" . local_try_number_format( $as['Extrapolated Filtered Q17 Mean Alignment Length']) ."</td>";
                                        print "<td>" . local_try_number_format( $as['Extrapolated Filtered Q20 Mean Alignment Length']) ."</td>";
                                        print "<td>" . local_try_number_format( $as['Extrapolated Filtered Q47 Mean Alignment Length']) ."</td>";
                                print "</tr>";

                                print "<tr>";
                                        print "<th>Longest Alignment [bp]</th>";
                                        print "<td>" . local_try_number_format( $as['Sampled Filtered Q17 Longest Alignment']) ."</td>";
                                        print "<td>" . local_try_number_format( $as['Sampled Filtered Q20 Longest Alignment']) ."</td>";
                                        print "<td>" . local_try_number_format( $as['Sampled Filtered Q47 Longest Alignment']) ."</td>";
                                        print "<td>" . local_try_number_format( $as['Extrapolated Filtered Q17 Longest Alignment']) ."</td>";
                                        print "<td>" . local_try_number_format( $as['Extrapolated Filtered Q20 Longest Alignment']) ."</td>";
                                        print "<td>" . local_try_number_format( $as['Extrapolated Filtered Q47 Longest Alignment']) ."</td>";
                                print "</tr>";

                                print "<tr>";
                                        print "<th>Mean Coverage Depth</th>";

                                        print "<td>" . local_try_number_format( $as['Sampled Filtered Q17 Mean Coverage Depth'], 2 ) ;
                                        print (is_numeric($as['Sampled Filtered Q17 Mean Coverage Depth']) ) ?  "&times; </td>" : " </td>" ;

                                        print "<td>" . local_try_number_format( $as['Sampled Filtered Q20 Mean Coverage Depth'], 2);
                                        print (is_numeric($as['Sampled Filtered Q20 Mean Coverage Depth']) ) ?  "&times; </td>" : " </td>" ;

                                        print "<td>" . local_try_number_format( $as['Sampled Filtered Q47 Mean Coverage Depth'], 2);
                                        print (is_numeric($as['Sampled Filtered Q47 Mean Coverage Depth']) ) ?  "&times; </td>" : " </td>" ;

                                        print "<td>" . local_try_number_format( $as['Extrapolated Filtered Q17 Mean Coverage Depth'],2);
                                        print (is_numeric($as['Extrapolated Filtered Q17 Mean Coverage Depth']) ) ?  "&times; </td>" : " </td>" ;

                                        print "<td>" . local_try_number_format( $as['Extrapolated Filtered Q20 Mean Coverage Depth'],2 );
                                        print (is_numeric($as['Extrapolated Filtered Q20 Mean Coverage Depth']) ) ?  "&times; </td>" : " </td>" ;

                                        print "<td>" . local_try_number_format( $as['Extrapolated Filtered Q47 Mean Coverage Depth'],2 );
                                        print (is_numeric($as['Extrapolated Filtered Q47 Mean Coverage Depth']) ) ?  "&times; </td>" : " </td>" ;
                                print "</tr>";

                                print "<tr>";
                                        //slightly special case because we only print % in the cell if the call has a number
                                        print "<th>Percentage of Library Covered</th>";

                                        print "<td>" . local_try_number_format( $as['Sampled Filtered Q17 Coverage Percentage']) ;
                                        print (is_numeric($as['Sampled Filtered Q17 Coverage Percentage']) ) ?  "% </td>" : " </td>" ;

                                        print "<td>" . local_try_number_format( $as['Sampled Filtered Q20 Coverage Percentage']);
                                        print (is_numeric($as['Sampled Filtered Q20 Coverage Percentage']) ) ?  "% </td>" : " </td>" ;

                                        print "<td>" . local_try_number_format( $as['Sampled Filtered Q47 Coverage Percentage']);
                                        print (is_numeric($as['Sampled Filtered Q47 Coverage Percentage']) ) ?  "% </td>" : " </td>" ;

                                        print "<td>" . local_try_number_format( $as['Extrapolated Filtered Q17 Coverage Percentage']);
                                        print (is_numeric($as['Extrapolated Filtered Q17 Coverage Percentage']) ) ?  "% </td>" : " </td>" ;

                                        print "<td>" . local_try_number_format( $as['Extrapolated Filtered Q20 Coverage Percentage']);
                                        print (is_numeric($as['Extrapolated Filtered Q20 Coverage Percentage']) ) ?  "% </td>" : " </td>" ;

                                        print "<td>" . local_try_number_format( $as['Extrapolated Filtered Q47 Coverage Percentage']);
                                        print (is_numeric($as['Extrapolated Filtered Q47 Coverage Percentage']) ) ?  "% </td>" : " </td>" ;

                                print "</tr>";

                                print "</tbody>";
                                print "</table>";

                        }
                        //TO-DO : Filename is hardcoded here
                        $filename = "alignTable.txt";
                        if(!file_exists($filename))
                            {
                                die("File - ".$filename." not found");
                            }
                        else
                             {
                              $filehandle=fopen($filename,"r");
                        $alignTable = local_tabs_parse_to_keys($filehandle);
	        	if ($alignTable){
			print "<h3 style='margin-left:-14px;'>Re-Alignment Read Distribution</h3>";
			print "<script>$('.tip').tipTip({ position : 'bottom' });</script>";
			print '<table style="width: 100%; margin-left:0px;" id="alignTable" class="heading">';
			print "<col width='15px'/>";
			print "<col width='15px'/>";
			print "<col width='15px' />";
			print "<col width='15px'/>";
			print "<col width='15px' />";
			print "<col width='15px' />";
			print "<col width='15px'/>";
			print "<col width='15px'/>";
		
			print "<tr>";
												
			print "<th><span class='tip float_right' title='The number of bases in each read </br> considered for the row in the table'>";
				print "<span class='tippy'>Read Length [bp]</span>";
			print "</span></th>";
		
			print "<th><span class='tip float_right' title='Number of reads with at least Read Length bases'>";
				print "<span class='tippy'>Reads</span>";
			print "</span></th>";
		
			print "<th><span class='tip float_right' title='Number of reads that tmap could not map'>";
				print "<span class='tippy'>Unmapped</span>";
			print "</span></th>";
		
			print "<th><span class='tip float_right' title='Number of reads mapped but not having 90% accuracy in first 50 bases'>";
				print "<span class='tippy'>Excluded</span>";
			print "</span></th>";
			
			print "<th><span class='tip float_right' title='Number of reads mapped and with accuracy > 90% in first 50 bases, </br> but with aligned length less than the Read Length threshold'>";
				print "<span class='tippy'>Clipped </span>";
			print "</span></th>";	
		
			print "<th><span class='tip float_right' title='Number of aligned reads with 0 mismatches in the first Read Length bases'>";
				print "<span class='tippy'>Perfect</span>";
			print "</span></th>";
		
			print "<th><span class='tip float_right' title='Number of aligned reads with one mismatch in the first Read Length bases'>";
				print "<span class='tippy'>1 mismatch</span>";
			print "</span></th>";
		
			print "<th><span class='tip float_right' title='Number of aligned reads with two or more </br>  mismatches in the first Read Length bases'>";
				print "<span class='tippy'>&ge;2 mismatches</span>";
			print "</span></th>";
		
			print "</tr>";	
		
			foreach ($alignTable as $key => $inarray) {
			    // if it is 0 it is a header
				$alignTableCol = 0;
				print "<tr>";
				foreach($inarray as $val) {
					if ($alignTableCol == 0){
						print "<th class='right_td'>";
					    print local_try_number_format($val);
						print "</th>";
					}elseif ($alignTableCol != 5){
						print "<td class='right_td'>";
					    print local_try_number_format($val);
						print "</td>";
					}
					$alignTableCol = $alignTableCol + 1;
				}
				print "</tr>";
			}
			print "</table>";
		}
}

?>
</body>
</html>
