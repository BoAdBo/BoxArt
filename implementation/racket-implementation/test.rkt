#lang racket

(provide (all-defined-out))

(define target (list "how" "are"));
(define corpus (list "how" "are" "you" "." "how" "well" "are" "you"));

(define (count-string target corpus)
  ;; target is string list
  ;; corpus, where count the occurrence of target in corpus

  ;; Algorithm:
  ;; 1. match target until it reaches null, add one to count and move to corpus next word
  ;; 2. if target doesn't match, move to corpus next word
  ;; 3. end at corpus null
  (letrec (
           ;; match-target match target to a sub-string of corpus.
           ;; return true if target reach the end(meaning the previous words of target all match)
           ;; 
           [match-target (lambda (tar cor)
                           (if (null? tar)
                               #t
                               (if (null? cor)
                                   #f
                                   (if (equal? (car tar) (car cor))
                                       (match-target (cdr tar) (cdr cor))
                                       #f))))]
           [next-corpus (lambda (cor count)
                          (if (null? cor)
                              count
                              (if (match-target target cor)
                                  (next-corpus (cdr cor) (+ count 1))
                                  (next-corpus (cdr cor) count))))])
    (next-corpus corpus 0)))

;; takes a sentence and output the probability computed using n-gram-model
;; sentence is a list of string
;; n as integer
;; don't accept n < 0
(define (n-gram-probability sentence n corpus)
  ;; compute word by word
  ;; construct previous n-word context

  ;; previous words contain the sequence of words reversed before the current word
  (letrec ([previos-words null]
           ;; need set!
           [context (lambda (seq-bef previous-words g)
                      ;; seq-bef        => sequence of words before current-word
                      ;; previous-words => the words sequence to pick
                      ;; g              => the remaining n-gram(remaining words needed to be added to seq-bef)
                      (if (<= g 0)
                          seq-bef
                          (if (null? previous-words)
                              (context (cons "<s>" seq-bef) null (- g 1))
                              (context (cons (car previous-words) seq-bef) (cdr previous-words) (- g 1)))))]
           [iter-by-word (lambda (un-processed previous-words)
                           ;; returns a list of pair of (word . (n-1)-tuple) regarding previous words sequence
                           (if (null? un-processed)
                               null
                               (let* ([context-seq (context null previous-words (- n 1))]
                                      [next (iter-by-word (cdr un-processed) (cons (car un-processed) previous-words))]
                                      [word-pair-context (cons context-seq (car un-processed))])
                                 (cons word-pair-context next))))]
           [count-in-corpus (lambda (produced-pairs)
                              (if (null? produced-pairs)
                                  null
                                  (let* ([cur (car produced-pairs)]
                                         [context-plus-word (append (car cur) (list (cdr cur)))]
                                         [context-without-word (car cur)]
                                         [dividend (count-string context-plus-word corpus)]
                                         [divider (count-string context-without-word corpus)])
                                    (cons (if (= divider 0)
                                              0
                                              (/ dividend divider)) (count-in-corpus (cdr produced-pairs))))))]
           [mul-all (lambda (xs)
                      (if (null? xs)
                          1
                          (* (car xs) (mul-all (cdr xs)))))])
    (mul-all (count-in-corpus (iter-by-word sentence null)))))
