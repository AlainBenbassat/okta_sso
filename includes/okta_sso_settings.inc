<?php

class OktaSsoSettings {
  public $disableLogin = FALSE;
  public $clientId = '';
  public $clientSecret = '';
  public $redirectUri = '';
  public $metadataUri = '';
  public $state = '';

  public function __construct() {
    if ($this->getOktaSsoSettings() === FALSE) {
      $msg = "
        Please add the following code in your settings.php file.<br>
        <pre>
          \$conf['okta_sso_settings'] = [
            'disable_login' => TRUE,
            'client_id' => 'SEE-YOUR-OKTA-DASHBOARD',
            'client_secret' => 'SEE-YOUR-OKTA-DASHBOARD',
            'redirect_uri' => 'https://YOUR-SITE/okta_sso',
            'metadata_uri' => 'SEE-YOUR-OKTA-DASHBOARD',
          ];
        </pre>
      ";
      throw new Exception($msg);
    }

    $this->generateStateString();
  }

  public function useSaml() {
    return FALSE;
  }

  public function useOauth() {
    return TRUE;
  }

  private function getOktaSsoSettings() {
    $oktaSsoSettings = variable_get('okta_sso_settings');

    $this->disableLogin = $oktaSsoSettings['disable_login'];
    $this->clientId = $oktaSsoSettings['client_id'];
    $this->clientSecret = $oktaSsoSettings['client_secret'];
    $this->redirectUri = $oktaSsoSettings['redirect_uri'];
    $this->metadataUri = $oktaSsoSettings['metadata_uri'];
  }

  private function generateStateString() {
    if ($_SESSION['okta_sso_state']) {
      $this->state = $_SESSION['okta_sso_state'];
    }
    else {
      $this->state = bin2hex(random_bytes(5));
    }
  }
}
