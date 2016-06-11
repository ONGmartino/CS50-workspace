<?php require("../includes/config.php"); 
	
    // if submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
		// require an exact old password, security purpose
        if($_POST["old_passwd"] == Null) apologize ("Enter your old password");   
        else if(password_verify ($_POST["old_passwd"], cs50::query("SELECT * FROM users WHERE id = ?", $_SESSION["id"])[0]["hash"]) != True)
                apologize("Please retype your old password");
        
		// check the correctness of the form
    	else if($_POST["password"] == Null) apologize("No password submitted");
    	else if($_POST["confirmation"] == Null) apologize("Please confirm your password");
    	else if($_POST["password"] != $_POST["confirmation"]) apologize("Password mismatch");
 
 		// then act: hash the pw and update the db, lastly redirect to home
		else 
		{
			$hash = password_hash($_POST["password"], PASSWORD_DEFAULT);
			cs50::query("UPDATE users SET hash = ? WHERE id= ?", $hash, $_SESSION["id"]); 
			header('Location: index.php');
		}
	}

	// if GET, render the page
	else
		render("passwd_req.php", ["title" => "Change password"]);
?>