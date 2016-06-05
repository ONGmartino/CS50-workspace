<?php

    // configuration
    require("../includes/config.php"); 

    // render portfolio
    $rows = cs50::query("SELECT symbol,shares FROM portfolios WHERE id = ?",$_SESSION["id"]);

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
                "value" => $row["shares"] * $stock["price"]
            ];
        }
    }
   
    $cash = number_format(cs50::query("SELECT cash FROM users WHERE id = ?",$_SESSION["id"])[0]["cash"],2);

    render("portfolio.php", ["title" => "Portfolio", "positions" => $positions, "cash" => $cash]);

?>

<!-- portfolios: id (session id), symbol, name (stock), price, shares
cash from users table -->