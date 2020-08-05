import React from "react";
import ReactDOM from "react-dom";
import Meter from "./meter";

class HelloMessage extends React.Component {
  render() {
    return (
      <div>
        <Meter></Meter>
      </div>
    );
  }
}

var mountNode = document.getElementById("app");
ReactDOM.render(<HelloMessage name="Jane" />, mountNode);
