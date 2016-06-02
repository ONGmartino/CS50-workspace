<div>
    <table class="table table-striped">
        <thead>
            <tr>
                <th>Symbol</th>
                <th>Name</th>
                <th>Shares</th>
                <th>Price</th>
                <th>Value</th>
            </tr>
        </thead>
        <tbody>
            <?php foreach ($positions as $position): ?>
                <tr>
                    <td><?= $position["symbol"] ?></td>
                    <td><?= $position["name"] ?></td>
                    <td><?= $position["shares"] ?></td>
                    <td><?= $position["price"] ?></td>  
                    <td><?= number_format($position["value"],2) ?></td>
                </tr>
            <?php endforeach ?>
            <tr>
                <td colspan="4" >CASH</td>
                <td><?= "$".$cash ?> </td>
            </tr>
        </tbody>
    </table>
</div>