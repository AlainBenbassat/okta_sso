<?php

class OktaSsoOauth {
  private $settings;

  public function __construct($settings) {
    $this->settings = $settings;
  }

  public function validate($code) {
    // get the meta data
    $metadata = OktaSsoConnection::httpRequest($this->settings->metadataUri, FALSE);

    // exchange the code for an access token
    $response = OktaSsoConnection::httpRequest($metadata->token_endpoint, $this->getParamsToken($code));

    // get the user info
    $token = OktaSsoConnection::httpRequest($metadata->introspection_endpoint, $this->getParamsIntrospection($response->access_token));

    if ($token->active) {
      return $token->username;
    }
    else {
      throw new Exception('Token is not active');
    }
  }

  public function getLoginUrl() {
    $metadata = OktaSsoConnection::httpRequest($this->settings->metadataUri, FALSE);
    $loginURL = $metadata->authorization_endpoint . '?' . http_build_query($this->getParamsAuthorization());

    return $loginURL;
  }

  private function getParamsAuthorization() {
    $params = [
      'response_type' => 'code',
      'client_id' => $this->settings->clientId,
      'redirect_uri' => $this->settings->redirectUri,
      'state' => $this->settings->state,
      'scope' => 'openid',
    ];

    return $params;
  }

  private function getParamsIntrospection($accessToken) {
    $params = [
      'client_id' => $this->settings->clientId,
      'client_secret' => $this->settings->clientSecret,
      'token' => $accessToken,
    ];
    return $params;
  }

  private function getParamsToken($code) {
    $params = [
      'code' => $code,
      'grant_type' => 'authorization_code',
      'client_id' => $this->settings->clientId,
      'client_secret' => $this->settings->clientSecret,
      'redirect_uri' => $this->settings->redirectUri,
    ];

    return $params;
  }
}
