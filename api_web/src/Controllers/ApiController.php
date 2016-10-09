<?php

namespace App\Controllers;

class ApiController extends Controller
{
	private $command_list = [
		"fac" => [
			"name" => "Expressões",
			"commands" => [
				"10" => 'Feliz',
				"20" => 'Feliz 2',
				"30" => 'Triste',
				"40" => 'Triste 2',
				"50" => 'Mostrando a lingua',
				"60" => 'XX',
				"70" => 'Assustado',
				"80" => 'Com sono',
				"90" => 'Falando'
			]
		],

		"mov" => [
			"name" => "Braços",
			"commands" => [
				"10" => 'Levantar braço Esquerdo',
				"20" => 'Levantar braço Direito',
				"30" => 'Levantar os dois braços',
				"40" => 'Abaixar os dois braços',
				"50" => 'Balançar os dois braços',
				"60" => 'Balançar os dois braços 2',
				"70" => 'Balançar os dois braços 3',
				"80" => 'Girar os dois braços',
				"90" => 'Assenar',
			]
		],
	];


	public function index($request, $response, $args)
	{
		$data = $request->getQueryParams();

		$this->response_type = (isset($data['type'])) ? $data['type'] : "html";
		$param = $this->checkCommand($data);

		if ( $param["param"] ) {
			if ( !isset($this->command_list[$param["param"]]["commands"][$param["command"]]) ) {
				$param = null;
			}

			return $this->response($request, $response, $param);
		}

		$this->ci->renderer->render($response, "index.phtml", [
			"command_list"=>$this->command_list,
			"request"=>$request
		]);
	}

	private function checkCommand($data)
	{
		$command = null;
		$param = null;

		if ( isset($data['fac']) ) {
			$param = "fac";
			$command = $data['fac'];
		}

		if ( isset($data['mov']) ) {
			$param = "mov";
			$command = $data['mov'];
		}

		return ["param" =>$param, "command"=>$command];
	}




	public function commandList($request, $response, $args)
	{
		$this->response_type = (isset($args['type'])) ? $args['type'] : "json";

		return $this->response($request, $response, $this->command_list, $args);
	}


	public function command($request, $response, $args)
	{
		$this->response_type = (isset($args['type'])) ? $args['type'] : "json";
		$command = (isset($args['command'])) ? $args['command'] : "";

		$this->response($request, $response, $this->command_list[$command]);
	}
}