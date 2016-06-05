<?php require("../includes/config.php"); 
	
    // if submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if($_POST["old_passwd"] == Null) apologize ("Enter your old password");   
        
        else if(password_verify ($_POST["old_passwd"], cs50::query("SELECT * FROM users WHERE id = ?", $_SESSION["id"])[0]["hash"]) != True)
                apologize("Please retype your old password");
        
    	else if($_POST["password"] == Null) apologize("No password submitted");
    	else if($_POST["confirmation"] == Null) apologize("Please confirm your password");
    	else if($_POST["password"] != $_POST["confirmation"]) apologize("Password mismatch");
 
		else 
		{
			$hash = password_hash($_POST["password"], PASSWORD_DEFAULT);
			cs50::query("UPDATE users SET hash = ? WHERE id= ?", $hash, $_SESSION["id"]); 
			header('Location: index.php');
		}
	}
	else
		render("passwd_req.php", ["title" => "Change password"]);
?>