<?php

    // configuration
    require("../includes/config.php"); 
    
    $tables = query("SELECT * FROM history WHERE id = ?",$_SESSION["id"]);
    
    $positions = [];
    foreach ($tables as $table)
    {
        $positions[] = [
            "action" => $table["action"],
            "date" => $table["date"],
            "symbol" => $table["symbol"],            
            "shares" => $table["shares"],
            "price" => $table["price"]
            ];
            
    }
        
    // render portfolio
    render("history_form.php", ["title" => "History", "positions" => $positions]);
?>
