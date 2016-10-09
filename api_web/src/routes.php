<?php
// Routes


$app->get('/', '\App\Controllers\ApiController:index');

$app->get('/command-list[/{type}]', '\App\Controllers\ApiController:commandList');

$app->get('/robot-api/v1/command/{command}[/{type}]', '\App\Controllers\ApiController:command');
