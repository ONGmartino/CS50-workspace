<form name="sell" action="sell.php" method=post>   
    <fieldset>
        <div class="form-group">
            <SELECT autofocus class="form-control" name="symbol">
                <option value=''>What you want to sell?</option>
                <?php 
                    foreach ($stocks as $stock)                         
                        print ("<option value='$stock'>".$stock."</option>");
                ?>
            </SELECT>
        </div>
        <div class="form-group">
            <input class="form-control" name="quantity" placeholder="Quantity" type="number"/>
        </div>
        <div class="control-group">
            <input class="form-control" type="submit" value="Sell now!"/>
        </div>
    </fieldset>
</form>