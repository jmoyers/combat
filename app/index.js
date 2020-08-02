import React from "react";
import ReactDOM from "react-dom";

class HelloMessage extends React.Component {
  render() {
    return (
      <div>
        <div class="row">
          <div class="col s3 grey">Fights</div>
          <div class="col s9 teal">Details</div>
        </div>
      </div>
    );
  }
}

var mountNode = document.getElementById("app");
ReactDOM.render(<HelloMessage name="Jane" />, mountNode);
