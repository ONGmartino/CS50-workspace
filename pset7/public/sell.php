<?php

    // configuration
    require("../includes/config.php");

    // if the form has been submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // sanity check
        if ($_POST["symbol"] == NULL) apologize ("Select a symbol");
        if ($_POST["quantity"] == NULL) apologize ("Enter a quantity");
        
        //find if allowed and new price
        $coverage = cs50::query("SELECT * from portfolios WHERE id=? AND symbol=?",
                    $_SESSION["id"],$_POST["symbol"])[0]["shares"];
        if ($coverage < $_POST["quantity"]) apologize("Sorry, you don't own them.");

        $new_price = lookup($_POST["symbol"])["price"];

	    // adding the value of share to cash
        cs50::query("UPDATE users SET cash = cash + ? WHERE id = ?", 
                    $new_price * $_POST["quantity"], $_SESSION["id"]);
        
	    // update portifolio quantity
        if($coverage == $_POST["quantity"])
            cs50::query("DELETE FROM portfolios WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]); 
        else
            cs50::query("UPDATE portfolios SET shares = shares - ? WHERE id = ? AND symbol = ?", 
                    $_POST["quantity"], $_SESSION["id"], $_POST["symbol"]);

	    // then update the history
        cs50::query("INSERT INTO history (id, type, symbol, shares, price) VALUES (?, ?, ?, ?, ?)", 
            $_SESSION["id"], "s", $_POST["symbol"], $_POST["quantity"], $new_price);
        
        redirect("./");
    }
    
    else
    {
        // query the portfolio, based on the pset specification elsewhere
        $rows =	cs50::query("SELECT * FROM portfolios WHERE id = ?", $_SESSION["id"]);	
        $stocks = [];
        foreach ($rows as $row)	$stocks[] = $row["symbol"];
        render("sell_req.php", ["title" => "Sell req", "stocks" => $stocks]);
    }
?>
