import { useState, useEffect } from "react";
import settings from "../settings.json";
import LightBulbOn from "../assets/lightbulb_on.jpg";
import LightBulbOff from "../assets/lightbulb_off.jpg";

function LightBulb() {
  const [isOn, setLight] = useState(false);

  useEffect(() => {
    const interval = setInterval(() => {
      fetch(`${settings.server_url}light`, { method: "GET" })
        .then((res) => res.json())
        .then((data) => {
          setLight(data.light);
        });
    }, 2000);

    return () => clearInterval(interval);
  }, []);
  return (
    <img
      src={isOn ? LightBulbOn : LightBulbOff}
      alt={isOn ? "On" : "Off"}
      width="400"
      height="300"
    />
  );
}

export default LightBulb;
