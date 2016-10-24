<?php

    // configuration
    require("../includes/config.php");
    
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a symbol.");
        }  
    
        $data = query("SELECT shares FROM users_portfolio WHERE id = ? and symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        if ($data === false)
        {
            apologize("There was an error.");
        }
        
        // number of shares
        $shares = $data[0]["shares"];
        
        // set action
        $action = 'SELL';
             
        // store the price in a variable
        $stock = lookup($_POST["symbol"]);
        $price = $stock["price"];
        
        // calculate money        
        $money = $price * $data[0]["shares"];
        
        // update cash
        query("UPDATE users SET cash = cash + ? WHERE id = ?", $money,  $_SESSION["id"]);
                       
        // sell shares
        query("DELETE FROM users_portfolio WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        
        // update history
        query("INSERT INTO history (id, action, symbol, shares, price) VALUES (?, ?, ?, ?, ?)", $_SESSION["id"], $action, $_POST["symbol"], $shares, $price);
                               
        //redirect to portfolio
        redirect("/");
    }
    else
    {   
        // query symbols from usesr portfolio    
        $rows = query("SELECT symbol FROM users_portfolio WHERE id = ?", $_SESSION["id"]);
        
        //create new array
        $stocks = [];
        
        // for each of stocks
        foreach ($rows as $row)
        {
            // get symbols
            $stock = $row["symbol"];
            
            // add symbol to new array
            $stocks[] = $stock;  
        }
       
               
        // else render form
        render("sell_form.php", ["title" => "Sell", "stocks" => $stocks]);
    }    
?>    
