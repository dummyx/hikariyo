import Chart from "./components/Charts";
import Control from "./components/Control";
import LightBulb from "./components/LightBulb";

function App() {
  
  return (
    <div className="App">
      <LightBulb />
      <div>
        <Control />
      </div>
      <div>
        <Chart />
      </div>
    </div>
  );
}

export default App;
