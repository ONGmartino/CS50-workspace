<?php

    // configuration
    require("../includes/config.php");

    // if the form has been submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $transaction = "SELL";
    //find new price
        $new_price = lookup($_POST["symbol"])[0]["shares"];
    //find old price/quantity
        $coverage = query("SELECT * from portfolios WHERE id=? AND symbol=?",
                    $_SESSION["id"],$_POST["symbol"])[0]["shares"];
        if ($coverage - $_POST("quantity") <0) apologize("Sorry, you don't own them.");

        // adding the value of share to cash
        query("UPDATE users SET cash = cash + ? WHERE id = ?", 
                    ($new_price * $_POST["quantity"], $_SESSION["id"]);
        
        // deleting stock from portifolios table
        query("DELETE FROM portfolios WHERE id = ? AND symbol = ?", 
                    $_SESSION["id"], $_POST["symbol"]);
        // Updating the history
        query("INSERT INTO history (id, transaction, symbol, shares, price) VALUES (?, ?, ?, ?, ?)", 
        $_SESSION["id"], $transaction, $_POST["symbol"], $stock2[0]["shares"], $stock1["price"]);
        
        // coming back to portifolio page
            redirect("./");
        
    }
    
    else
    {
        // query the portfolio, based on the pset specification elsewhere
        $rows =	query("SELECT * FROM portfolios WHERE id = ?", $_SESSION["id"]);	
        $stocks = [];
        foreach ($rows as $row)	{   
            $stock = $row["symbol"];
            $stocks[] = $stock;       
        }    

        // render sell form
        render("sell_form.php", ["title" => "Sell Form", "stocks" => $stocks]);
    }
?>
