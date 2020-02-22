package main

import (
	"fmt"
	"net/http"

	"github.com/dengsgo/math-engine/engine"
)

// 知乎问题 https://www.zhihu.com/question/365763395 如何优雅地利用c++编程从1乘到20？
func main() {
	http.HandleFunc("/calculator", calculator)
	http.ListenAndServe(":8080", nil)
}

func calculator(w http.ResponseWriter, r *http.Request) {
	expression := r.FormValue("expression")
	result, err := engine.ParseAndExec(expression)
	if err != nil {
		w.Write([]byte(fmt.Sprintf("%s", err)))
	} else {
		w.Write([]byte(fmt.Sprintf("%f", result)))
	}
}
