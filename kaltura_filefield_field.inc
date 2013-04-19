<?php

/**
 * Implementation of hook_field_settings_alter().
 */
function kaltura_filefield_field_settings_alter(&$settings, $op, $field) {
  if ($field['type'] == 'filefield') {
    switch ($op) {
      case 'form':
        $player_id = ($field['kaltura_player_id']) ? $field['kaltura_player_id'] : NULL;
        $settings['kaltura_player_id'] = array(
          '#type' => 'textfield',
          '#title' => t('Kaltura Player ID'),
          '#default_value' => $player_id,
          '#required' => FALSE,
          '#size' => '15',
          '#weight' => 0,
          '#element_validate' => array('_element_validate_integer_positive'),          
          );
        $kaltura_use_thumbnail = ($field['kaltura_use_thumbnail']) ? $field['kaltura_use_thumbnail'] : NULL;
        $settings['kaltura_use_thumbnail'] = array(
          '#type' => 'checkbox',
          '#title' => t('Embed a Clickable Player Thumbnail'),
          '#description' => t('Insert a thumbnail that is replaced by a Kaltura player when clicked 
            (useful when you have multiple players on a single page). You may override the thumbnail in your css.'),
          '#default_value' => $kaltura_use_thumbnail,
          '#required' => FALSE,
          '#size' => '15',
          '#weight' => 0,
          ); 
        break;
      case 'save':
        $settings[] = 'kaltura_player_id';
        $settings[] = 'kaltura_use_thumbnail';        
        break;
    }
  }
}

/**
* Implementation of hook_theme().
*/
function kaltura_filefield_theme() {
  return array(
    // Themes for the formatters.
    'kaltura_filefield_formatter_player' => array(
      'arguments' => array('element' => NULL),
    ),   
  );
}

/**
* Implementation of hook_field_formatter_info().
* 
*/
function kaltura_filefield_field_formatter_info() {
  return array(
    'player' => array(
      'label' => t('Kaltura Filefield Player'),
      'field types' =>  array('filefield'),
      'multiple values' => CONTENT_HANDLE_CORE,
    ),
  );
}

/**
* Theme function for Kaltura Filefield Player
* 
* Override this in your theme directory if you want to add your own js params
* or perform other customizations.
* 
* @param array $element
*  A cck field element array 
*/
function theme_kaltura_filefield_formatter_player($element) {
  $field = content_fields($element['#field_name']);
  if ($player_id = $field['kaltura_player_id']) {
    $config       = kaltura_filefield_config();
    $entry_id     = kaltura_filefield_entry_id_get($element['#item']['fid']);
    $type         = $element['#type_name'];
    $partner_id   = $config['kaltura_partner_id'];
    $embed_method = ($field['kaltura_use_thumbnail']) ? 'kWidget.thumbEmbed' : 'kWidget.embed';
    $player = 
      "<div id=\"$entry_id\" class=\"clearfix kaltura-player kaltura-player-$type player-$player_id\"></div> 
      <script src=\"http://cdnapi.kaltura.com/p/$partner_id/sp/$partner_id/embedIframeJs/uiconf_id/$player_id/partner_id/$partner_id\"></script>
      <script>
            $embed_method({
               'targetId': '$entry_id',
               'wid': '_$partner_id',
               'uiconf_id': '$player_id',
               'entry_id': '$entry_id',
               'playBtn': '$thumb_id',
               'flashvars':{ // flashvars allows you to set runtime uiVar configuration overrides. 
                    'autoPlay': false
               },
               'params':{ // params allows you to set flash embed params such as wmode, allowFullScreen etc
                    'wmode': 'transparent'
               },
       });
      </script>";
    return $player;
  }
  else {
    return t('Player ID Missing from Field Settings');
  }
}
