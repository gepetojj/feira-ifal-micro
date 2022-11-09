const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="pt-br">
	<head>
		<meta charset="UTF-8" />
		<meta name="viewport" content="width=device-width, initial-scale=1.0" />
		<title>Alexa com ESP-32</title>

		<style>
			body {
				margin: 0;
				padding: 0;
				box-sizing: border-box;
				font-family: "Segoe UI", Tahoma, Geneva, Verdana, sans-serif;
				background-color: rgb(1, 1, 12);
				overflow-x: hidden;
			}

			.hidden {
				display: none;
			}

			#alert[class=""] {
				display: flex;
				justify-content: center;
				align-items: center;

				width: 100%;
				height: 100vh;

				background: rgb(89, 25, 25);
				background: linear-gradient(
					137deg,
					rgba(89, 25, 25, 1) 0%,
					rgba(196, 32, 32, 1) 49%,
					rgba(213, 214, 49, 1) 100%
				);
			}

			#alert > p {
				font-size: 2rem;
				text-align: center;
				color: white;
			}

			#status {
				width: 100vw;
				padding: 0.5rem;
				text-align: center;
				opacity: 0;
				transition: 0.25s all ease-in-out;
			}

			section {
				display: flex;
				flex-direction: column;
				width: 100vw;
				height: 95vh;
				color: white;
				text-align: center;
			}

			.transcript-parent {
				display: flex;
				justify-content: center;
				align-items: center;
			}

			.transcript {
				width: 100%;
				max-width: 30rem;
				border: 1px solid white;
				border-radius: 0.3rem;
				padding: 1rem;
			}

			#speak {
				padding: 0.5rem 1rem;
			}
		</style>
	</head>
	<body>
		<div id="alert" class="hidden">
			<p>Seu navegador não suporta a função de reconhecimento por voz.</p>
		</div>
		<main id="main" class="hidden">
			<div id="status">Ouvindo...</div>
			<section>
				<h1>Alexa com ESP-32</h1>
				<p>Permita acesso ao seu microfone, fale algo, e veja o resultado no ESP-32.</p>
				<div class="transcript-parent">
					<div class="transcript">
						<p>Pedido: <span id="transcript"></span></p>
            			<p>Resposta: <span id="response"></span></p>
						<button type="button" id="speak" onclick="speechRecog.start();" disabled>
							Aperte para falar
						</button>
					</div>
				</div>
			</section>
		</main>

		<script defer>
			function processResponse(message) {
				const response = document.getElementById("response");
				response.innerText = message;

				const tts = new SpeechSynthesisUtterance();
				tts.lang = "pt-BR";
				tts.text = message;
				window.speechSynthesis.speak(tts);
			}

			function processCommand(command) {
				command = command.toLowerCase();

				if (command.includes("led")) {
					if (command.includes("ligar") || command.includes("ligue") || command.includes("acenda")) {
						fetch("/led/ligar").then(res => res.text().then(data => processResponse(data ?? "OK")));
					}
					else if (command.includes("desligar") || command.includes("desligue") || command.includes("apague")) {
						fetch("/led/desligar").then(res => res.text().then(data => processResponse(data ?? "OK")));         
					}
					else if (command.includes("piscar") || command.includes("pisque")) {
						fetch("/led/blink").then(res => res.text().then(data => processResponse(data ?? "OK")));
					}
				}
        		else if (command.includes("temperatura")) {
          			fetch("/temp").then(res => res.text().then(data => processResponse(`A temperatura atual é ${data ?? "?"} graus celsius.`)));
        		}
				else if (command.includes("som")) {
					fetch("/buzzer").then(res => res.text().then(data => processResponse(data ?? "OK")));
				}
			}
		</script>

		<script defer>
			if ("webkitSpeechRecognition" in window) {
				document.getElementById("main").className = "";
			} else {
				document.getElementById("alert").className = "";
				console.error("Navegador não suporta reconhecimento vocal!");
			}

			const speechRecog = new webkitSpeechRecognition();

			const statusElement = document.getElementById("status");
			const speakButton = document.getElementById("speak");

			speechRecog.interimResults = true;
			speechRecog.lang = "pt-BR";

			speechRecog.start();

			speechRecog.onstart = () => {
				statusElement.innerText = "Ouvindo...";
				statusElement.style.opacity = "1";
				statusElement.style.backgroundColor = "green";
				speakButton.disabled = true;

				const timeout = setTimeout(() => (statusElement.style.opacity = "0"), 5000);
				return () => clearTimeout(timeout);
			};

			speechRecog.onspeechstart = speechRecog.onstart;

			speechRecog.nomatch = () => {
				statusElement.innerText = "Não entendi o que disse.";
				statusElement.style.opacity = "1";
				statusElement.style.backgroundColor = "yellow";
				speakButton.disabled = false;

				const timeout = setTimeout(() => (statusElement.style.opacity = "0"), 5000);
				return () => clearTimeout(timeout);
			};

			speechRecog.onerror = (err) => {
				statusElement.innerText = "Houve um erro.";
				statusElement.style.opacity = "1";
				statusElement.style.backgroundColor = "red";
				speakButton.disabled = false;

				console.error(err);
				if (err.error === "no-speech") {
					statusElement.innerText = "Nenhuma fala foi reconhecida.";
				} else if (err.error === "not-allowed") {
					statusElement.innerText = "Conceda permissão de acesso ao seu microfone.";
				}

				const timeout = setTimeout(() => (statusElement.style.opacity = "0"), 5000);
				return () => clearTimeout(timeout);
			};

			speechRecog.onresult = (event) => {
				let finalTranscript = "";
				let interimTranscript = "";

				for (let i = event.resultIndex; i < event.results.length; ++i) {
					if (event.results[i].isFinal) {
						finalTranscript += event.results[i][0].transcript;
					} else {
						interimTranscript += event.results[i][0].transcript;
					}
				}

				const transcriptElement = document.getElementById("transcript");
				transcriptElement.innerText = finalTranscript || interimTranscript;
				finalTranscript
					? (transcriptElement.style.fontStyle = "normal")
					: (transcriptElement.style.fontStyle = "italic");

				processCommand(finalTranscript);

				statusElement.innerText = "Fala reconhecida com sucesso.";
				statusElement.style.opacity = "1";
				statusElement.style.backgroundColor = "green";
				speakButton.disabled = false;

				const timeout = setTimeout(() => (statusElement.style.opacity = "0"), 5000);
				return () => clearTimeout(timeout);
			};
		</script>
	</body>
</html>
)=====";