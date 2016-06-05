<form action="passwd.php" method="post">
    <fieldset>
        <div class="form-group">
            <input autofocus class="form-control" name="old_passwd" placeholder="Old password" type="password"/>
        </div>        
        <div class="form-group">
            <input autofocus class="form-control" name="password" placeholder="New password" type="password"/>
        </div>
        <div class="form-group">
            <input class="form-control" name="confirmation" placeholder="Retype it" type="password"/>
        </div>
        <div class="form-group">
            <button type="submit" class="btn btn-default">Change password</button>
        </div>
    </fieldset>
</form>