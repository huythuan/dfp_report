<?php
/**
 * @file
 * Theme implementation to display the Google Analytics summary.
 */
?>
<div style="width:100%;">
  <div>
    <h3 style="text-transform: capitalize;"><?php print $date ; ?> Report:</h3>
	<h3>This is a report for <?php print $summary[1][1]; ?> with AD id is: <?php print print $summary[1][0];?>:</h3>
  </div>
	<table style="width:100%">
    <tr style="background: #e4e4e4;">
	  <th style ="width:20%;padding:2px 0;"><?php print t('LINE_ITEM_NAME'); ?></th>
	  <td style ="width:20%;padding:2px 0;"><?php print $summary[1][1]; ?></td>
      <th style ="width:20%;padding:2px 0;"><?php print t('AD_SERVER_IMPRESSIONS'); ?></th>
      <td style ="width:20%;padding:2px 0;"><?php print $summary[1][2]; ?></td>

    </tr>
    <tr style="background: #efefef;">
	  <th style ="width:20%;padding:2px 0;"><?php print t('AD_SERVER_CLICKS'); ?></th>
      <td style ="width:20%;padding:2px 0;"><?php print $summary[1][3]; ?></td>
	  <th style ="width:20%;padding:2px 0;"><?php print t('AD_SERVER_CTR'); ?></th>
      <td style ="width:20%;padding:2px 0;"><?php print $summary[1][4]; ?></td>
     
    </tr>
    <tr style="background: #e4e4e4;">
      <th style ="width:20%;padding:2px 0;"><?php print t('AD_SERVER_CPM_AND_CPC_REVENUE'); ?></th>
	  <td style ="width:20%;padding:2px 0;"><?php print $summary[1][5]; ?></td>
	  <th style ="width:20%;padding:2px 0;"><?php print t('AD_SERVER_WITHOUT_CPD_AVERAGE_ECPM'); ?></th>
      <td style ="width:20%;padding:2px 0;"><?php print $summary[1][6]; ?></td>
    </tr>
  </table>
</div>