import { useState } from "react";

import settings from "../settings.json";
import logo from "../assets/iwi.png";

function Control() {
  const [secret, setSecret] = useState("");

  function doClick() {
    fetch(`${settings.server_url}set_command?secret=${secret}`, {
      method: "POST",
    });
  }
  return (
    <>
      <button onClick={doClick}>
        <img src={logo} className="App-logo" alt="iwi" />
      </button>
      <br/>
      <input
        type="password"
        placeholder="password"
        onChange={(e) => setSecret(e.target.value)}
      />
    </>
  );
}

export default Control;
