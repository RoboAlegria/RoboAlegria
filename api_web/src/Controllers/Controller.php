<?php

namespace App\Controllers;

class Controller
{
	protected $ci;

	protected $response_type;

	public function __construct(\Slim\Container  $ci)
	{
		$this->ci = $ci;
	}

	protected function response($request, $response, $data=[], $args=[])
	{
		return $this->checkResponteType($request, $response, $data);
	}

	private function checkResponteType($request, $response, $data)
	{
		switch ($this->response_type) {
			case 'json':
				$n_response = $response->withJson($data);
				break;

			case 'html':
				$response_data = ['request'=>$request, 'data'=>$data];
				$n_response = $this->ci->renderer->render($response, 'command.phtml', $response_data);
				break;
			
			default:
				$n_response = $response->getBody()->write("response type not defined");
				break;
		}

		return $n_response;
	}

}