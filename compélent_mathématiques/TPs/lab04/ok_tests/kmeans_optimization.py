test = {
  'name': 'kmeans_optimization',
  'points': 1,
  'suites': [
    {
      'cases': [
        {
          'code': r"""
          >>> y_gd = np.linalg.norm(X[:,None] - c[None,:], axis=2).argmin(1);
          >>> 
          >>> c_pred = np.stack([np.mean(X[y_gd==i], axis=0) for i in range(3)], axis=0);
          >>> c_True = np.stack([np.mean(X[y==i], axis=0) for i in range(3)], axis=0);
          >>> 
          >>> error = lambda i: np.linalg.norm(c_pred[i] - c_True, axis=1).min();
          >>> 
          >>> error(0), error(1), error(2)
          78c30956cd369e93454788692e5f1afd
          # locked
          """,
          'hidden': False,
          'locked': True
        }
      ],
      'scored': True,
      'setup': '',
      'teardown': '',
      'type': 'doctest'
    }
  ]
}
