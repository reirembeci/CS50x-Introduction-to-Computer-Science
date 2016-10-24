<?php

    // configuration
    require("../includes/config.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["password"]))
        {
            apologize("You must provide your old password.");
        }
        else if (empty($_POST["new_password"]))
        {
            apologize("You must provide your new password.");
        }
        else if (empty($_POST["confirmation"]))
        {
            apologize("You must confirm your new password.");
        }
                
        // validate password match
        $row =  query("SELECT hash FROM users WHERE id = ?", $_SESSION["id"]);
        $old_password = $row[0]["hash"];
        
        if ($_POST["new_password"] != $_POST["confirmation"])
        {
            apologize("Your passwords don't match.");
        }    
        
        if (crypt($_POST["password"], $old_password) !== $old_password)
        {
            apologize("You entered a wrong password.");
        }
        else
        {
            //update new password
            $update = query("UPDATE users SET hash = ? WHERE id = ?", crypt($_POST["new_password"]), $_SESSION["id"]);
            if ($update === false)
            {
                apologize("We couldn't save your new passowrd. Try again.");
            }
            
            //redirect to portfolio
            redirect("/");                                                                       
        }                   
    }    
    else
    {
        // else render form
        render("password_form.php", ["title" => "Change your password"]);
    }

?>
