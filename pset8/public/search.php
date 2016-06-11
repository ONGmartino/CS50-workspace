<?php

    require(__DIR__ . "/../includes/config.php");

    // numerically indexed array of places
    $places = [];

    // query with a fullindex and in natural language. 
    // not sure how to implement the "autosuggestion" that should require the "LIKE" parameters 
    $places = cs50::query("SELECT * FROM places WHERE MATCH (postal_code, place_name) AGAINST (?* IN NATURAL LANGUAGE MODE) LIMIT 10", $_GET["geo"]);

    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>