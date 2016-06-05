<div>
    <table class="table table-hover">
        <thead>
            <tr>
                <th class="text-center">Symbol</th>
                <th class="text-center">Name</th>
                <th class="text-center">Shares</th>
                <th class="text-center">Price</th>
                <th class="text-center">Value</th>
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
            <tr class="info">
                <td colspan="3">CASH</td>
                <td colspan="3"> <?= "$".$cash ?> </td>
            </tr>
        </tbody>
    </table>
</div>