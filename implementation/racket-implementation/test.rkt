#lang racket

(provide (all-defined-out))

(define target (list "how"));
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
(define (n-gram-probability sentence n)
  ;; compute word by word
  ;; construct previous n-word context

  ;; let previous-words be a stream that when evaluated provide the necessary previous words-context
  (letrec ([previos-words ()]
           [context (lambda )])))
