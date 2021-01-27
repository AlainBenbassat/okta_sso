<?php

class OktaSsoConnection {
  public static function httpRequest($url, $params = FALSE) {
    $ch = curl_init($url);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
    if ($params) {
      curl_setopt($ch, CURLOPT_POSTFIELDS, http_build_query($params));
    }

    return json_decode(curl_exec($ch));
  }
}
