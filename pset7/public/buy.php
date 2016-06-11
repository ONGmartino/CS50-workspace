<?php

    // configuration, as usual
    require("../includes/config.php");

    // if the form has been submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        //find if allowed and new price
        $tmp = lookup($_POST["symbol"]);
        $coverage = cs50::query("SELECT * from users WHERE id=?", $_SESSION["id"])[0]["cash"];

        if (($_POST["quantity"] * $tmp["price"]) > $coverage) 
            apologize("Sorry, enought fund.");

        // add item to portfolio (or insert a new one)            
        cs50::query("INSERT INTO portfolios (id, symbol, name, price, shares) 
                     VALUES (?, ?, ?, ((price * shares)+?) / (shares + ?), ?)
                     ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)",
            $_SESSION["id"], $_POST["symbol"], $tmp["name"], $tmp["price"]*$_POST["quantity"],
            $_POST["quantity"] ,$_POST["quantity"]); 

        // subtract the value of share to cash
        cs50::query("UPDATE users SET cash = cash - ? WHERE id = ?", 
                    $tmp["price"] * $_POST["quantity"], $_SESSION["id"]);

	    // then update the history
        cs50::query("INSERT INTO history (id, type, symbol, shares, price) VALUES (?, ?, ?, ?, ?)", 
                     $_SESSION["id"], "b", $_POST["symbol"], $_POST["quantity"], $tmp["price"]);

        redirect("./");
    }
    
    else
    {
        // render sell form
        render("buy_req.php", ["title" => "Buy req"]);
    }
?>
