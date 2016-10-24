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
        
        // store the result in a variable
        $stock = lookup($_POST["symbol"]);
        
        // validate if a valid symbol for an actual stock is submitted
        if ($stock === false)
        {
            apologize("You must provide an actual stock symbol.");
        }
        
        // call render 
        $symbol = $stock['symbol'];
        $name = $stock['name'];
        $price = $stock['price'];        
        render("quote_display.php", ['symbol' => $symbol, 'name' => $name, 'price' => number_format($price, 2) ]);        
    }
    else
    {
        // else render form
        render("quote_form.php", ["title" => "Quote"]);
    }    
?>    
