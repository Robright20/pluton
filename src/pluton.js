import React, {useState, useEffect} from "react";

function Pluton(props) {
  const [canvas, setCanvas] = useState({});

  useEffect(() => {
    if (canvas instanceof HTMLCanvasElement) {
      const ctx = canvas.getContext('2d');
      props.startDraw({canvas, ctx});
    }
    else
      setCanvas(document.getElementById('canvas'));
  }, [canvas]);

  useEffect(() => {
    console.log('->pluton');
    console.log(canvas.height, canvas.width);
  });
  return (
    <canvas
      id="canvas"
      width={props.canvasWidth}
      height={props.canvasHeight}>
    </canvas>
  );
}

export default Pluton;