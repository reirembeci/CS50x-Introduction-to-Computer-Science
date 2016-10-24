<form action="sell.php" method="post">
    <fieldset>
        <div class="form-group">
            <select class="form-control" name="symbol">
                <option value=""> </option>
                <?php
                    foreach ($stocks as $symbol)	
                    {
                        // print options
                        echo("<option value='$symbol'>" . strtoupper($symbol) . "</option>");
                    }
                ?>     
            </select>
        </div>
        <div class="form-group">
            <button type="submit" class="btn btn-default">Sell</button>
        </div>
    </fieldset>
</form>
