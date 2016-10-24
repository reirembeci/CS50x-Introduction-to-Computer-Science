<?php

    // configuration
    require("../includes/config.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["username"]))
        {
            apologize("You must provide your username.");
        }
        else if (empty($_POST["password"]))
        {
            apologize("You must provide your password.");
        }
        else if (empty($_POST["confirmation"]))
        {
            apologize("You must confirm your password.");
        }
        
        // validate password 
        if ($_POST["password"] != $_POST["confirmation"])
        {
            apologize("Your passwords don't match.");
        }
        
        // add user to database and check for errors
        $result = query("INSERT INTO users (username, hash, cash) VALUES(?, ?, 10000.00)", $_POST["username"], crypt($_POST["password"]));
        
        if ($result === false)
        {
            apologize("The username you entered already exists. Please enter a new one.");
        }
        
        // once registered, log them in automatically
        
        // find out their id
        $rows = query("SELECT LAST_INSERT_ID() AS id");
        $id = $rows[0]["id"];
        
        // store their id in session
        $_SESSION["id"] = $id;
        
        //redirect to index
        redirect("/");
        
    }
    
    else
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

?>
