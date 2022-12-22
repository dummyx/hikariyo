import React, { useState } from "react";
import logo from "./assets/iwi.png";
import "./App.css";
import settings from "./settings.json";

import Chart from "./components/Charts";

function App() {
  const [secret, setSecret] = useState("");

  function doClick() {
    fetch(`${settings.server_url}set_command?secret=${secret}`, {
      method: "POST",
    });
  }
  return (
    <div className="App">
      <header className="App-header">
        <button onClick={doClick}>
          <img src={logo} className="App-logo" alt="iwi" />
        </button>
        <input
          type="password"
          placeholder="password"
          onChange={(e) => setSecret(e.target.value)}
        />
      </header>
      <div>
        <Chart />
      </div>
    </div>
  );
}

export default App;
