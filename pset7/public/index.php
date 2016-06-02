<?php

    // configuration
    require("../includes/config.php"); 

    // render portfolio
    $row = query("SELECT symbol,shares FROM portfolios WHERE id = ?",$_SESSION["id"]);

    $positions = [];
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
                "value" => number_format($row["shares"] * $stock["price"],2)
            ];
        }
    }
   
    $cash = query("SELECT cash FROM users WHERE id = ?",$_SESSION["id"])[0]["cash"];

    render("portfolio.php", ["title" => "Portfolio", "positions" => $positions, "cash" => $cash]);

?>

<!-- portfolios: id (session id), symbol, name (stock), price, shares
cash from users table -->