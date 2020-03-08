#ifndef INDEX_H
#define INDEX_H

/*
 * Saves the webpage to flash memory. You can use any html you would like, 
 * just replace everything between "R"=====(" and ")=====";".
 * For more info see: https://github.com/lukehod/wifi-power-button
 */
const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<title>RPi Power Control</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3.css">
<link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.12.1/css/all.css" integrity="sha384-v8BU367qNbs/aIZIxuivaU55N5GPF89WBerHoGA4QTcbUjYiLQtKdrfXnqAcXyTv" crossorigin="anonymous">

<style>
body {
  min-height: 100vh;
}
.main {
  min-height: 100vh;
}
.cell {
  text-align: center;
  margin: 40px 0 40px 0;
}
#button {
  box-shadow: 0 8px 16px 0 rgba(0,0,0,0.2), 0 6px 20px 0 rgba(0,0,0,0.19);
}
</style>

<body style="min-height:100vh;">
  <div class="w3-display-container w3-light-grey main">
    <div class="w3-container w3-padding-large w3-teal w3-center">
      <h1>RPi Power Control</h1>
    </div>
    <div class="w3-cell-row w3-display-middle">
      <div class="w3-cell w3-mobile cell">
        <a href="power" class="w3-button w3-jumbo w3-black w3-round-large" id="button"><i class="fas fa-power-off"></i></a>
      </div>
      <div class="w3-cell w3-mobile cell">
        <a href="led" class="w3-button w3-jumbo w3-black w3-round-large" id="button"><i class="fas fa-lightbulb"></i></a>
      </div>
    </div>
  </div>
</body>

</html>
)=====";

#endif
