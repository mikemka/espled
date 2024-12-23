#include "settings.h"
#include "network_functions.h"

String SendHTML () {
  String ptr = R"(

<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
  <title>LED Control</title>
  <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-QWTKZyjpPEjISv5WaRU9OFeRpok6YctnYmDr5pNlyT2bRjXh0JMhjY6hW+ALEwIH" crossorigin="anonymous">
  <link rel="stylesheet" href="https://cdn.jsdelivr.net/gh/mdbassit/Coloris@latest/dist/coloris.min.css"/>
  <style>
    body {
      padding-top: 20px;
    }
    .color-input {
      margin-bottom: 15px;
    }
  </style>
</head>
<body class="bg-dark text-light">
  <div class="container">
    <h1 class="mb-4">ESPLED</h1>
    <div class="row">
      <div class="col-md-6 color-input">
        <label for="color1" class="form-label">Color for LED 5</label>
        <input type="text" id="color1" data-coloris>
      </div>
      <div class="col-md-6 color-input">
        <label for="color2" class="form-label">Color for LED 12</label>
        <input type="text" id="color2" data-coloris>
      </div>
    </div>
    <pre id="status" class="mt-3"></pre>
  </div>
  <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js" integrity="sha384-YvpcrYf0tY3lHB60NNkmXc5s9fDVZLESaAA55NDzOxhy9GkcIdslK1eN7N6jIeHz" crossorigin="anonymous"></script>
  <script src="https://cdn.jsdelivr.net/gh/mdbassit/Coloris@latest/dist/coloris.min.js"></script>
  <script>
  function hexToRgb(hex) {
    var result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
    return result ? {
      r: parseInt(result[1], 16),
      g: parseInt(result[2], 16),
      b: parseInt(result[3], 16)
    } : null;
  }

  function debounce(func, wait) {
    let timeout;
    return function executedFunction(...args) {
      const later = () => {
        clearTimeout(timeout);
        func(...args);
      };
      clearTimeout(timeout);
      timeout = setTimeout(later, wait);
    };
  }

  let color1 = { r: 0, g: 0, b: 0 };
  let color2 = { r: 0, g: 0, b: 0 };

  const sendColorRequest = debounce(() => {
    const url = `/setcolor?r_5=${color1.r}&g_5=${color1.g}&b_5=${color1.b}&r_12=${color2.r}&g_12=${color2.g}&b_12=${color2.b}`;
    fetch(url)
      .then(response => response.text())
      .then(data => {
        document.getElementById('status').textContent = data;
      })
      .catch(error => {
        document.getElementById('status').textContent = 'Error: ' + error.message;
      });
  }, 50);

  document.addEventListener('coloris:pick', event => {
    const rgb = hexToRgb(event.detail.color);
    if (rgb) {
      if (event.detail.currentEl.id === 'color1') {
        color1 = rgb;
      } else if (event.detail.currentEl.id === 'color2') {
        color2 = rgb;
      }
      sendColorRequest();
    }
  });

  // Initialize Coloris
  Coloris({
    themeMode: 'dark',
    alpha: false
  });
  </script>
</body>
</html>

)";
  return ptr;
}
