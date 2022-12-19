import React from 'react';
import logo from './assets/iwi.png'
import './App.css';



function App() {
  function doClick() {
    console.log("clicked")
  }
  return (
    <div className="App">
      <header className="App-header">
        <button onClick={doClick}>
          <img src={logo} className="App-logo" alt="iwi" />
        </button>
        <p>
          Edit <code>src/App.tsx</code> and save to reload.
        </p>
        <a
          className="App-link"
          href="https://reactjs.org"
          target="_blank"
          rel="noopener noreferrer"
        >
          Learn React
        </a>
      </header>
    </div>
  );
}

export default App;
