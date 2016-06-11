<?php

    // configuration
    require("../includes/config.php"); 

    // query for the portfolio
    $rows = cs50::query("SELECT symbol,shares FROM portfolios WHERE id = ?",$_SESSION["id"]);
    $positions = [];

    // for each title, show the current price 
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "price" => $stock["price"],
                "shares" => $row["shares"],
                "symbol" => $row["symbol"],
                "value" => $row["shares"] * $stock["price"]
            ];
        }
    }
    
    // and the avaliable wallet
    $cash = number_format(cs50::query("SELECT cash FROM users WHERE id = ?",$_SESSION["id"])[0]["cash"],2);

    // then finally rended
    render("portfolio.php", ["title" => "Portfolio", "positions" => $positions, "cash" => $cash]);
?>

