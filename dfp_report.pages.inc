<?php
/**
 * @file
 */
/**
 * Page callback for the 'goauth/authenticate' path.
 *
 * This page callback does every kind of authorizations.
 */
function dfp_report_authenticate_page() {
  $code = isset($_GET['code']) ? $_GET['code'] : NULL;
  set_include_path('sites/all/libraries/googleads-php-lib-master/src/');
  $path = libraries_get_path('googleads-php-lib-master');
  require_once $path.'/src/Google/Api/Ads/Dfp/Lib/DfpUser.php';
  try {
	  $oauth2Info = array(
	    'client_id' => variable_get('dfp_report_client_id'),
	    'client_secret' => variable_get('dfp_report_client_secret')
	  );

	  // See DfpUser constructor
	  $user = new DfpUser(NULL, NULL, NULL, NULL, NULL, NULL, NULL, $oauth2Info);
	  $user->LogDefault();
      // Get the OAuth2 credential.
	  $redirectUri = variable_get('dfp_report_redirect_uri');
	  $offline = TRUE;
	  // Get the authorization URL for the OAuth2 token.
	  // No redirect URL is being used since this is an installed application. A web
	  // application would pass in a redirect URL back to the application,
	  // ensuring it's one that has been configured in the API console.
	  // Passing true for the second parameter ($offline) will provide us a refresh
	  // token which can used be refresh the access token when it expires.
	  $OAuth2Handler = $user->GetOAuth2Handler();
	  
	  // Get the access token using the authorization code. Ensure you use the same
	  // redirect URL used when requesting authorization.
	  $user->SetOAuth2Info(
		     $OAuth2Handler->GetAccessToken(
		     $user->GetOAuth2Info(), $code, $redirectUri));
	  $oauth2Info = $user->GetOAuth2Info();

	} catch (OAuth2Exception $e) {
	  drupal_set_message(t('Cannot authenticate. %string.', array('%string' => $e->getMessage())), 'error');
	} catch (ValidationException $e) {
	  drupal_set_message(t('Cannot authenticate. %string.', array('%string' => $e->getMessage())), 'error');
	} catch (Exception $e) {
	  drupal_set_message(t('Cannot authenticate. %string.', array('%string' => $e->getMessage())), 'error');
	}
  $info = '<p><b>Refresh Token:</b> ';
  if(!isset($e)){
	if(isset($oauth2Info['refresh_token'])){ 
    	variable_set('dfp_report_refresh_token', $oauth2Info['refresh_token']);
    }
    drupal_set_message(t('Authentication Success'), 'status');
    $info = $info.variable_get('dfp_report_refresh_token').'</p>';
  }
  $build = array(
  	'header_text' => array(
  		'#type' => 'markup',
        '#markup' => $info 
    )
  );
  return $build;
}
/**
 * Admin settings form.
 */
function dfp_report_admin_settings_form($form, &$form_state) {
  $form = array();
  
  $form['dfp_report_application_name'] = array(
    '#title' => t('Application Name'),
    '#type' => 'textfield',
    '#default_value' => variable_get('dfp_report_application_name'),
  );

  $form['dfp_report_client_id'] = array(
    '#title' => t('Client ID'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => variable_get('dfp_report_client_id'),
  );

  $form['dfp_report_client_secret'] = array(
    '#title' => t('Client Secret'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => variable_get('dfp_report_client_secret'),
  );

  $form['dfp_report_redirect_uri'] = array(
    '#title' => t('Redirect URI'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => variable_get('dfp_report_redirect_uri'),
  );

  $form['dfp_report_network_code'] = array(
    '#title' => t('DFP Network Code'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => variable_get('dfp_report_network_code'),
    '#description' =>t('This code can get from DFP account.'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}


/*
 * config form submit
 */
function dfp_report_admin_settings_form_submit($form, &$form_state) {
	set_include_path('sites/all/libraries/googleads-php-lib-master/src/');
	$path = libraries_get_path('googleads-php-lib-master');
	require_once $path.'/src/Google/Api/Ads/Dfp/Lib/DfpUser.php';
  	try {
	  $oauth2Info = array(
	    'client_id' => $form_state['values']['dfp_report_client_id'],
	    'client_secret' => $form_state['values']['dfp_report_client_secret']
	  );

	  // See DfpUser constructor
	  $user = new DfpUser(NULL, NULL, NULL, NULL, NULL, NULL, NULL, $oauth2Info);
	  $user->LogDefault();
      // Get the OAuth2 credential.
	  $redirectUri = $form_state['values']['dfp_report_redirect_uri'];
	  $offline = TRUE;
	  // Get the authorization URL for the OAuth2 token.
	  // No redirect URL is being used since this is an installed application. A web
	  // application would pass in a redirect URL back to the application,
	  // ensuring it's one that has been configured in the API console.
	  // Passing true for the second parameter ($offline) will provide us a refresh
	  // token which can used be refresh the access token when it expires.
	  $OAuth2Handler = $user->GetOAuth2Handler();
	  $authorizationUrl = $OAuth2Handler->GetAuthorizationUrl(
	      $user->GetOAuth2Info(), $redirectUri, $offline);

	} catch (OAuth2Exception $e) {
	  drupal_set_message(t('Cannot authenticate. Error: %string.', array('%string' => $e->getMessage())), 'error');
	} catch (ValidationException $e) {
	  drupal_set_message(t('Cannot authenticate. Error: %string.', array('%string' => $e->getMessage())), 'error');
	} catch (Exception $e) {
	  drupal_set_message(t('Cannot authenticate. Error: %string.', array('%string' => $e->getMessage())), 'error');
	}
  variable_set('dfp_report_application_name', $form_state['values']['dfp_report_application_name']);
  variable_set('dfp_report_client_id', $form_state['values']['dfp_report_client_id']);
  variable_set('dfp_report_client_secret', $form_state['values']['dfp_report_client_secret']);
  variable_set('dfp_report_redirect_uri', $form_state['values']['dfp_report_redirect_uri']);
  variable_set('dfp_report_network_code', $form_state['values']['dfp_report_network_code']);
  drupal_set_message('In Order To Complete Authenticate, Please Click <a href="'.$authorizationUrl.'">Here</a>.','status');
} // google_dfp_blocks_config_form_submit()

/**
* Page for authentication form setting
*/
function dfp_report_page_settings_auth() {
  $build = array(
  	'header_text' => array(
  		'#type' => 'markup',
        '#markup' => '<p>'.t('Please get input for this form, and click save').'</p>'
  	),
    'dfp_report_form' => drupal_get_form('dfp_report_admin_settings_form'),
  );
  return $build;
}
/**
* Page for reporting
*/
function dfp_report_page_report() {	
	//dfp_report_get_inventory_report();
	/*
	$build = array(
  	'header_text' => array(
  		'#type' => 'markup',
        '#markup' => '<p>'.t('Matched Unites:'.$matchedUnits ).'</p>'.
                     '<p>'.t('Available Unites:'.$availableUnits ).'</p>'.
					 '<p>'.t('Percent Available Units:'.$percentAvailableUnits ).'</p>'
  	),
  );
  return $build;
*/
drupal_add_library('system', 'drupal.ajax');
$form = drupal_get_form('dfp_report_inventory_form');
$render = drupal_render($form);
$build['my_div'] = array(
  '#markup' => '<div id="dfp_inventory">'.$render .'</div>',
);
$build['ajax_link'] = array(
  '#type' => 'link',
  '#title' => t('Click here'),
  // Note the /nojs portion of the href - if javascript is enabled,
  // this part will be stripped from the path before it is called.
  '#href' => 'dfp-report/ajax-callback/nojs/',
  '#id' => 'ajax_link',
  '#ajax' => array(
    'wrapper' => 'dfp_inventory',
    'method' => 'html',
  ),
);
return $build;


}

/**
* Page for getting report
*/
function dfp_report_get_inventory_report() {
	set_include_path('sites/all/libraries/googleads-php-lib-master/src/');
	$path = libraries_get_path('googleads-php-lib-master');
    require_once $path.'/src/Google/Api/Ads/Dfp/Lib/DfpUser.php';
    require_once $path.'/src/Google/Api/Ads/Dfp/Util/DateTimeUtils.php';
    require_once $path.'/src/Google/Api/Ads/Dfp/Util/StatementBuilder.php';
    require_once $path. '/examples/Common/ExampleUtils.php';
	try {
	   $oauth2Info = array(
	    'client_id' => variable_get('dfp_report_client_id'),
	    'client_secret' => variable_get('dfp_report_client_secret'),
	    'refresh_token' => variable_get('dfp_report_refresh_token')
	  );
	   $applicationName = variable_get('dfp_report_application_name');
	   $networkCode = variable_get('dfp_report_network_code');

	  // See DfpUser constructor
	  $user = new DfpUser(NULL, NULL, NULL, $applicationName, $networkCode,
	      NULL, NULL, $oauth2Info);
	  
	  	 // Log SOAP XML request and response.
		  $user->LogDefaults();

		// Get the LineItemService.
		  $lineItemService = $user->GetService('LineItemService', 'v201411');

		  // Create a statement to select all line items.
		  $statementBuilder = new StatementBuilder();
		  $statementBuilder->OrderBy('id ASC')
		      ->Limit(StatementBuilder::SUGGESTED_PAGE_LIMIT);

		  // Default for total result set size.
		  $totalResultSetSize = 0;

		  do {
		    // Get line items by statement.
		    $page = $lineItemService->getLineItemsByStatement(
		        $statementBuilder->ToStatement());

		    // Display results.
		    if (isset($page->results)) {
		      $totalResultSetSize = $page->totalResultSetSize;
		      $i = $page->startIndex;
		      foreach ($page->results as $lineItem) {
		        printf("%d) Line item with ID %d, belonging to order %d, and name '%s' "
		            . "was found.\n", $i++, $lineItem->id, $lineItem->orderId,
		            $lineItem->name);
		      }
		    }

		    $statementBuilder->IncreaseOffsetBy(StatementBuilder::SUGGESTED_PAGE_LIMIT);
		  } while ($statementBuilder->GetOffset() < $totalResultSetSize);
	} catch (OAuth2Exception $e) {
	  drupal_set_message(t('1 %string.', array('%string' => $e->getMessage())), 'error');
	} catch (ValidationException $e) {
	  drupal_set_message(t('2 %string.', array('%string' => $e->getMessage())), 'error');
	} catch (Exception $e) {
	  drupal_set_message(t('3 %string.', array('%string' => $e->getMessage())), 'error');
	}
	

}



/**
* An Ajax callback which will load some new text for the heading tag.
*/

function test_ajax_ajax_call_back($type = 'ajax') {
	$t = dfp_report_get_inventory_report();
//	sleep(60);
if($type == 'ajax'){
//	$t = dfp_report_get_inventory_report();
                $commands = array();
                $commands[] = ajax_command_html('#dfp_inventory',$t);
                $commands[]= ajax_command_changed('#dfp_inventory');
                $page = array('#type' =>'ajax', '#commands' =>$commands);
                ajax_deliver($page);

}else{
                $output = t('This is what should be seen if Javascript is not enable.');
                return $output;

  }

}