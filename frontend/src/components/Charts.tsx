import React, { useState, useEffect } from "react";
import settings from "../settings.json";

import {
  Chart as ChartJS,
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend,
} from "chart.js";
import { Line } from "react-chartjs-2";

ChartJS.register(
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend
);

export const options = {
  responsive: true,
  plugins: {
    legend: {
      position: "top" as const,
    },
    title: {
      display: true,
      text: "Chart.js Line Chart",
    },
  },
};

type Data = {
  time: string;
  light: number;
  temperature: number;
  humidity: number;
  pressure: number;
};

type GetDataType = {
  data: Data[];
};

function Chart() {
  const [data, setData] = useState<GetDataType>({
    data: [{ time: "", light: 0, temperature: 0, humidity: 0, pressure: 0 }],
  });

  useEffect(() => {
    fetch(`${settings.server_url}get_data`, { method: "GET" })
      .then((res) => res.json())
      .then((data) => {
        setData(data);
      });
  }, []);

  let list = data.data;

  const chartData = {
    labels: list.map((entry) => entry.time),
    datasets: [
      {
        label: "Raw birghtness value",
        data: list.map((entry) => entry.light),
      },
      {
        label: "Temperature",
        data: list.map((entry) => entry.temperature),
      },
      {
        label: "Humidity",
        data: list.map((entry) => entry.humidity),
      },
      {
        label: "Pressure",
        data: list.map((entry) => entry.pressure),
      },
    ],
  };

  return <Line options={options} data={chartData} />;
}

export default Chart;
