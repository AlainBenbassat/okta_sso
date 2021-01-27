<?php

class OktaSsoFactory {
  public static function getAuthenticator($settings) {
    if ($settings->useOauth()) {
      $o = new OktaSsoOauth($settings);
    }
    else {
      $o = new OktaSsoSaml($settings);
    }

    return $o;
  }
}
