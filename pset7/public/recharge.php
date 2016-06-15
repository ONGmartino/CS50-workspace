<?php

    // configuration
    require("../includes/config.php");

    // if the form has been submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // check the value
		if( $_POST["value"] == NULL ||
			!is_numeric($_POST["value"]) ||
			$_POST["value"] <= 0 ) 
				apologize("Invalid import");

		else{
		    // adding the deposit import
			cs50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $_POST["value"], $_SESSION["id"]);

			// then update the history
	        cs50::query("INSERT INTO history (id, type, price) VALUES (?, ?, ?)", $_SESSION["id"], "d", $_POST["value"]);

			// finally,
			redirect("./");
		}
    }
    
    else
    {
        // show the form
        render("recharge_form.php", ["title" => "Recharge your account"]);
    }
?>
