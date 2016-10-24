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
        else if (empty($_POST["shares"]))
        {
            apologize("You must provide the number of shares you want to buy.");
        }      
        
        // if symbol is invalid
        if (lookup($_POST["symbol"]) === false)
        {
            // apologize
            apologize("You must provide a valid stock symbol.");
        }
        
        // if shares is invalid (not a whole positive integer)
        if (preg_match("/^\d+$/", $_POST["shares"]) == false)
        {
            // apologize
            apologize("You must enter a whole, positive integer.");
        }
        
        // set action
        $action = 'BUY';
        
        // query the cash of the user
        $cash = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        
        // store the price in a variable
        $stock = lookup($_POST["symbol"]);
        $price = $stock["price"];
        
        // value of money to spend
        $value = $price * $_POST["shares"];
        
        // validate if the user can afford the stock
        if ($cash[0]["cash"] < $value)
        {
            apologize("You can't afford to buy the stock.");    
        }
        else 
        {
            //buy stocks (even more of the same stock)
            query("INSERT INTO users_portfolio (id, symbol, shares) VALUES(?, ? , ?) ON DUPLICATE KEY UPDATE shares = shares + ?", $_SESSION["id"], $_POST["symbol"], $_POST["shares"], $_POST["shares"]);
            
            // update cash
            query("UPDATE users SET cash = cash - ? WHERE id = ?", $value, $_SESSION["id"]);
            
            // update history
            query("INSERT INTO history (id, action, symbol, shares, price) VALUES (?, ?, ?, ?, ?)", $_SESSION["id"], $action, strtoupper($_POST["symbol"]), $_POST["shares"], $price);
        }
    
        //redirect to portfolio
        redirect("/");   
    }
    else
    {
        // else render form
        render("buy_form.php", ["title" => "Buy"]);
    }

?>
