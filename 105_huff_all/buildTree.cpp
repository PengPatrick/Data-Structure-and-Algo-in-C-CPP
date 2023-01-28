#include "node.h"

Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t pq;
  for (size_t i = 0; i < 257; i++) {
    if (counts[i] != 0) {
      pq.push(new Node(i, counts[i]));
    }
  }
  while (pq.size() >= 2) {
    Node * p = pq.top();
    pq.pop();
    Node * q = pq.top();
    pq.pop();
    Node * n = new Node(p, q);
    pq.push(n);
  }
  return pq.top();
}
