<?php require("../includes/config.php");
    
    // query for the cash, history voices, than render
    
    $cash = number_format(cs50::query("SELECT cash FROM users WHERE id = ?",$_SESSION["id"])[0]["cash"],2);  
    
    $hists = cs50::query("SELECT * from history WHERE id=?",$_SESSION["id"]);
  
    render("history_req.php", ["title" => "History", "cash" => $cash, "hists" => $hists]);
    
?>