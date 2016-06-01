<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("quote_req.php", ["title" => "Stocks"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
		if ($_POST["symbol"] == NULL) apologize("Empty field: symbol");
		$quotation = lookup($_POST["symbol"]);
        if ($quotation == false) apologize("Symbol not found!");
        
        else
            render("quote_get.php",
            [   "title" => "Quotation",
                "symbol" => $quotation["symbol"],
                "name" => $quotation["name"],
                "price" => $quotation["price"]
            ]
            );
    }
?>