<?php
/**
 * @file
 * Theme implementation to display the Google Analytics summary.
 */
?>
<?php
switch ($date) {
    case "daily":
        $time = date('m/d/Y', strtotime('yesterday'));
        $report='Report for day: '.$time;
        break;
    case "weekly":
        $week_start = date('m/d/Y', strtotime('last week monday'));
		$week_end = date('m/d/Y', strtotime('last week sunday'));
		$report = 'Report From: '.$week_start.' To '.$week_end;
        break;
    case "monthly":
        $first = date('m/d/Y', strtotime('first day of last month'));
		$last = date('m/d/Y', strtotime('last day of last month'));
		$report = 'Report From: '.$first.' To '.$last;
        break;
	default:
			$report = $date;
}
?>
<div style="width:100%;">
  <div>
    <h3 style="text-transform: capitalize;"><?php print $report ; ?></h3>
	<h3><?php print $title; ?></h3>
  </div>
	<table style="width:100%">
    <tr style="background: #e4e4e4;">
      <th style ="width:30%;padding:2px 0;"><?php print t('IMPRESSIONS'); ?></th>
      <td style ="width:20%;padding:2px 0;"><?php print $summary[1][2]; ?></td>

    </tr>
    <tr style="background: #efefef;">
	  <th style ="width:20%;padding:2px 0;"><?php print t('CLICKS'); ?></th>
      <td style ="width:20%;padding:2px 0;"><?php print $summary[1][3]; ?></td>
    </tr>
    <tr style="background: #e4e4e4;">
      <th style ="width:20%;padding:2px 0;"><?php print t('CTR (Click Through Ratio)'); ?></th>
      <td style ="width:20%;padding:2px 0;"><?php print ((float)$summary[1][4])*100; ?>%</td>
    </tr>
  </table>
</div>