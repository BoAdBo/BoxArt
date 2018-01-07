(+ 1 2)

(prin1 1)

(current-buffer)

;; when evaluating expression interactively, the
;; interpreter first reads the textual representation of it
;; producing a lisp object

;; That object is not necessarily evaluated to be value


;; Input Functions
;; Evaluation

#@COUNT (current-buffer) COUNT

#|| (current-buffer) ||#


;; The floating-point type uses c double to store
;; When an integer reads too large it will be treated as float

1e309
1e308

;; Characters in strings and buffers are currently limited to the range of 0 to 4194303-twenty two bits

;; A "symbol" is an object with a name, much like a variable
;; but it can serve as a variable or function name, or to hold a property list
;; Or it may serve only to be distinct from all other lisp objects,
;; so that its presence in a data structure may be recognized reliably

;; ":" keyword symbol

(setq \1 1) ;; \ can force interpreter to recognize it as symbol

\t

;; common lisp note: In common lisp, lower case letters are always folder to upper case

foo
FOO
1+
\-1 \+1

\(*\ 1\ 2\) ;; a symbol named '(* 1 2), this is the worst, bad bad choice for symbol

(setq #:foo1 1)

foo1

'(this list has (a list inside of it))

'(1 2 3 (1 2 3))


'list

(car '(1))

(car '(nil))

;; The single apostrophe, "'", in front of the example lists
;; is called a "quote". It tells Lisp to do nothing with the list
;; other than take it as it is written.
'(this is a quoted list)

;; But if there is no quote
;; the first item of the list is special.
;; It is a command for the computer to obey, an operator
(+ 2 2)

(this is an unquoted list)

;; eval-last-sexp, 'eval' is an evaluate, 'sexp' is symbolic expression

(error x)

(error (x))

(setq counter (lambda (x) (+ 2 x)))


;; The defun Macro

;; template
(defune FUNCITON-NAME (ARGUMENTS...)
  "OPTIONAL-DOCUMENTATION..."
  (interactive ARGUMENT-PASSING-INFO) ; optional
  BODY...)

(defune multiply-by-seven (number)
  "Multiply NUMBER by seven."
  (* 7 number))


