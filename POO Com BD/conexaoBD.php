<?php

$endereco = 'localhost';
$banco = 'CMP1611 - GUILHERME';
$usuario = 'postgres';
$senha = '190600';


try {
    $pdo = new PDO("pgsql:host=$endereco;port=5432;dbname=$banco", $usuario, $senha, [PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION]);
    echo "conectado";
} catch (PDOException $e) {
   echo "Falha ao Conectar. <br/>";
   die($e->getMessage());
}
?>