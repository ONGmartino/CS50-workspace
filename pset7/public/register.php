<?php

    // configuration
    require("../includes/config.php");

    // if a GET, render the usual registration form
    if ($_SERVER["REQUEST_METHOD"] == "GET")
      render("register_form.php", ["title" => "Register"]);

    // else if submitted though POST
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // firstly check the form
		if ($_POST["username"] == NULL) apologize("Empty field: username");
        if ($_POST["password"] == NULL) apologize("Empty field: passwd");
        if ($_POST["password"] != $_POST["confirmation"]) apologize("Passwd mismatch");
        
        // then insert the new user with the hashed pw, meanwhile check if username has been used before
        else{
            $ins = CS50::query("INSERT IGNORE INTO users (username, hash, cash) VALUES(?, ?, 10000.0000)",
                                $_POST["username"], password_hash($_POST["password"], PASSWORD_DEFAULT));
            if ($ins == false) apologize ("DB error. Please, try a different username");

            // if everything ok, save the ID cookie and redirect to home. 
            else {
                 $_SESSION["id"] = CS50::query("SELECT LAST_INSERT_ID() AS id")[0]["id"];
                 header('Location: index.php');        
            }
        }
    }

?>