<?php

    // configuration
    require("../includes/config.php"); 
    
    $rows = query("SELECT symbol, shares FROM users_portfolio WHERE id = ?", $_SESSION["id"]);
    $user_row = query("SELECT * FROM users WHERE id = ?",$_SESSION["id"]);
    $cash = $user_row[0]["cash"];
      
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
                "total" => $stock["price"] * $row["shares"]
            ];
        }
    }    
    

    // render portfolio
    render("portfolio.php", ["positions" => $positions, "title" => "Portfolio", "cash" => $cash]);

?>
