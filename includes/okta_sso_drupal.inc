<?php

class OktaSsoDrupal {
  public static function isUserLoggedIn() {
    global $user;

    if ($user->uid) {
      return TRUE;
    }
    else {
      return FALSE;
    }
  }

  public static function loadUserByName($userName) {
    global $user;

    $user = user_load_by_name($userName);
    if ($user === FALSE) {
      // no luck by name, try email
      $user = user_load_by_mail($userName);
    }

    if ($user === FALSE) {
      throw new Exception("There is no account for $userName");
    }

    if ($user->status != "1") {
      throw new Exception("The user $userName is blocked");
    }

    return $user;
  }

  public static function loginUser($user) {
    $params = ['name' => $user->name];
    user_login_finalize($params);
  }
}
